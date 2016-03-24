#include "calchash.h"
#include "openssl/hmac.h"
#include "openssl/sha.h"
#include "string.h"

CalcHash::CalcHash()
{

}
void CalcHash::calc_pmk(const char *key, char *essid_pre, unsigned char pmk[40] )
{
    int i, j, slen;
    unsigned char buffer[65];
    char essid[33+4];
    SHA_CTX ctx_ipad;
    SHA_CTX ctx_opad;
    SHA_CTX sha1_ctx;

    memset(essid, 0, sizeof(essid));
    memcpy(essid, essid_pre, strlen(essid_pre));
    slen = strlen( essid ) + 4;

    /* setup the inner and outer contexts */

    memset( buffer, 0, sizeof( buffer ) );
    strncpy( (char *) buffer, key, sizeof( buffer ) - 1 );

    for( i = 0; i < 64; i++ )
        buffer[i] ^= 0x36;

    SHA1_Init( &ctx_ipad );
    SHA1_Update( &ctx_ipad, buffer, 64 );

    for( i = 0; i < 64; i++ )
        buffer[i] ^= 0x6A;

    SHA1_Init( &ctx_opad );
    SHA1_Update( &ctx_opad, buffer, 64 );

    /* iterate HMAC-SHA1 over itself 8192 times */

    essid[slen - 1] = '\1';
    HMAC(EVP_sha1(), (unsigned char *)key, strlen(key), (unsigned char*)essid, slen, pmk, NULL);
    memcpy( buffer, pmk, 20 );

    for( i = 1; i < 4096; i++ )
    {
        memcpy( &sha1_ctx, &ctx_ipad, sizeof( sha1_ctx ) );
        SHA1_Update( &sha1_ctx, buffer, 20 );
        SHA1_Final( buffer, &sha1_ctx );

        memcpy( &sha1_ctx, &ctx_opad, sizeof( sha1_ctx ) );
        SHA1_Update( &sha1_ctx, buffer, 20 );
        SHA1_Final( buffer, &sha1_ctx );

        for( j = 0; j < 20; j++ )
            pmk[j] ^= buffer[j];
    }

    essid[slen - 1] = '\2';
    HMAC(EVP_sha1(), (unsigned char *)key, strlen(key), (unsigned char*)essid, slen, pmk+20, NULL);
    memcpy( buffer, pmk + 20, 20 );

    for( i = 1; i < 4096; i++ )
    {
        memcpy( &sha1_ctx, &ctx_ipad, sizeof( sha1_ctx ) );
        SHA1_Update( &sha1_ctx, buffer, 20 );
        SHA1_Final( buffer, &sha1_ctx );

        memcpy( &sha1_ctx, &ctx_opad, sizeof( sha1_ctx ) );
        SHA1_Update( &sha1_ctx, buffer, 20 );
        SHA1_Final( buffer, &sha1_ctx );

        for( j = 0; j < 20; j++ )
            pmk[j + 20] ^= buffer[j];
    }
}


void CalcHash::calc_ptk(unsigned char *pmk, unsigned char pke[], unsigned char *ptk)
{
    /* compute the pairwise transient key*/
    for (int i = 0; i < 4; i++)
    {
        pke[99] = i;
        HMAC(EVP_sha1(), pmk, 32, pke, 100, ptk + i * 20, NULL);
    }
}

void CalcHash::calc_mic(int wpaKeyVer, unsigned char *ptk, unsigned char *eapol, int eapolSize, unsigned char *mic)
{
    if (wpaKeyVer == 1)
        HMAC(EVP_md5(), ptk, 16, eapol, eapolSize, mic, NULL);
    else
        HMAC(EVP_sha1(), ptk, 16, eapol, eapolSize, mic, NULL);
}

CalcHash::~CalcHash(void)
{

}
