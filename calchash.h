#ifndef CALCHASH_H
#define CALCHASH_H


class CalcHash
{
   public: unsigned char pmk[40];
           unsigned char ptk[80];
           unsigned char mic[20];

public:
    CalcHash();
    void calc_pmk(const char *key, char *essid, unsigned char pmk[40] );
    void calc_ptk( unsigned char *pmk, unsigned char pke[100], unsigned char *ptk );
    void calc_mic( int wpaKeyVer, unsigned char *ptk, unsigned char *eapol, int eapolSize, unsigned char *mic );
    ~CalcHash();

};

#endif // CALCHASH_H
