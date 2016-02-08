#ifndef COMMON_H
#define COMMON_H

typedef struct{
    char essid[36]; // Имя точки доступа
    unsigned char bssid[6];
    unsigned char stmac[6];
    unsigned char snonce[32];
    unsigned char anonce[32];
    unsigned char eapol[256];
    int eapol_size;
    int keyver;
    unsigned char keymic[16];
} hccap_t;

#endif // COMMON_H
