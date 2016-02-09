#ifndef CALCPROC_H
#define CALCPROC_H
#include <QThread>
#include <keybox.h>
#include <calchash.h>
#include "common.h"

class CalcProc : public QThread
{
    Q_OBJECT
private:
    KeyBox* keyBox;
    hccap_t* hccap;
    CalcHash* calc;

public:
    CalcProc(KeyBox* keyBox, hccap_t* hccap, CalcHash* calc);
        void run();

    signals:
        void resultReady();
};

#endif // CALCPROC_H
