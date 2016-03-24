#include "calcproc.h"
#include "QTime"

CalcProc::CalcProc(KeyBox* keyBox, hccap_t* hccap, CalcHash* calc)
{
    this->keyBox = keyBox;
    this->hccap = hccap;
    this->calc = calc;
}

void CalcProc::run()
{
    QTime time;
    int iter = 0;
    char essid_pre[32];
    memset(essid_pre, 0, 32);
    memcpy(essid_pre, hccap->essid, 8);

    uchar pke[100];
    memset(pke, 0, 100);
    memcpy( pke, "Pairwise key expansion", 23 );
    if( memcmp( hccap->stmac, hccap->bssid, 6 ) < 0 )    {
        memcpy( pke + 23, hccap->stmac, 6 );
        memcpy( pke + 29, hccap->bssid, 6 );
    } else {
        memcpy( pke + 23, hccap->bssid, 6 );
        memcpy( pke + 29, hccap->stmac, 6 );
    }
    if( memcmp( hccap->snonce, hccap->anonce, 32 ) < 0 ) {
        memcpy( pke + 35, hccap->snonce, 32 );
        memcpy( pke + 67, hccap->anonce, 32 );
    } else {
        memcpy( pke + 35, hccap->anonce, 32 );
        memcpy( pke + 67, hccap->snonce, 32 );
    }
    time.start();
    while(1)
    {

        calc->calc_pmk(keyBox->GetKey().toStdString().c_str(), essid_pre, calc->pmk);

        calc->calc_ptk( calc->pmk, pke, calc->ptk );

        calc->calc_mic(3, calc->ptk, hccap->eapol, hccap->eapol_size, calc->mic);

        if (memcmp(calc->mic, hccap->keymic, 16) == 0)
        {
            emit resultReady("OK" + QString::number(keyBox->GetNumber()));
            break;
        } //else emit resultReady("FAIL");
        iter++;
        if(time.elapsed() >= 1000)
        {
           time.restart();
           emit resultReady(QString::number(iter) + " - " + QString::number(keyBox->GetNumber()));
           iter = 0;
        }
    }
}
