#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "vault.h"

void h(char *h);
void p(char *a, char *b);
unsigned r(unsigned v, short a);
unsigned *c(unsigned *k);
unsigned *m(const char *msg, int mlen);

typedef union uwb {
    unsigned w;
    unsigned char b[4];
} wb;

typedef unsigned Digest[4];

unsigned f0(unsigned efgh[])
{
    return (efgh[1] & efgh[2]) | (~efgh[1] & efgh[3]);
}

unsigned f1(unsigned efgh[])
{
    return (efgh[3] & efgh[1]) | (~efgh[3] & efgh[2]);
}

unsigned f2(unsigned efgh[])
{
    return efgh[1] ^ efgh[2] ^ efgh[3];
}

unsigned f3(unsigned efgh[])
{
    return efgh[2] ^ (efgh[1] | ~efgh[3]);
}

typedef unsigned (*DgstFctn)(unsigned a[]);

unsigned *c(unsigned *k)
{
    double s, pwr;
    int i;

    pwr = pow(2, 32);
    for (i = 0; i < 64; i++)
    {
        s = fabs(sin(1 + i));
        k[i] = (unsigned)(s * pwr);
    }
    return k;
}

unsigned r(unsigned v, short a)
{
    unsigned msk1 = (1 << a) - 1;
    return ((v >> (32 - a)) & msk1) | ((v << a) & ~msk1);
}

void p(char *a, char *b)
{
    char d[8];
    int c = 0;
    int l = -1089;
    while (*a && *b)
    {
        l += *a * *b;
        a++;
        b++;
    }
    while (l > 0)
    {
        d[c++] = (l % 10) % 2 == 0 ? 'a' + (l % 10) / 2 : '1' + (l % 10) - 1;
        l /= 10;
    }
    while (*a)
    {
        l += *a ^ 1;
        a++;
    }
    while (*b)
    {
        l += *b ^ 2;
        b++;
    }
    d[c++] = (l % 10) % 2 == 0 ? 'a' + (l % 10) / 2 : '1' + (l % 10) - 1;
    l /= 10;
    d[c++] = (l % 10) % 2 == 0 ? 'a' + (l % 10) / 2 : '1' + (l % 10) - 1;
    d[c] = '\0';

    h(d);
}

void h(char *h)
{
    wb u;
    int j, k;
    unsigned *d = m(h, strlen(h));
    char a[33];
    int c = 0;
    for (j = 0; j < 4; j++)
    {
        u.w = d[j];
        for (k = 0; k < 4; k++)
        {
            int i = u.b[k] / 16;
            a[c++] = i < 10 ? '0' + i : 'a' + i - 10;
            i = u.b[k] % 16;
            a[c++] = i < 10 ? '0' + i : 'a' + i - 10;
        }
    }
    a[c++] = '\0';
    check(a);
}

unsigned *m(const char *msg, int mlen)
{
    static Digest h0 = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
    static DgstFctn ff[] = {&f0, &f1, &f2, &f3};
    static short M[] = {1, 5, 3, 7};
    static short O[] = {0, 1, 5, 0};
    static short rot0[] = {7, 12, 17, 22};
    static short rot1[] = {5, 9, 14, 20};
    static short rot2[] = {4, 11, 16, 23};
    static short rot3[] = {6, 10, 15, 21};
    static short *rots[] = {rot0, rot1, rot2, rot3};
    static unsigned kspace[64];
    static unsigned *k;

    static Digest h;
    Digest efgh;
    DgstFctn fctn;
    short m, o, g;
    unsigned f;
    short *rotn;
    union {
        unsigned w[16];
        char b[64];
    } mm;
    int os = 0;
    int grp, grps, q, p;
    unsigned char *msg2;

    if (k == NULL)
        k = c(kspace);

    for (q = 0; q < 4; q++)
        h[q] = h0[q];

    {
        grps = 1 + (mlen + 8) / 64;
        msg2 = malloc(64 * grps);
        memcpy(msg2, msg, mlen);
        msg2[mlen] = (unsigned char)0x80;
        q = mlen + 1;
        while (q < 64 * grps)
        {
            msg2[q] = 0;
            q++;
        }
        {
            wb u;
            u.w = 8 * mlen;
            q -= 8;
            memcpy(msg2 + q, &u.w, 4);
        }
    }

    for (grp = 0; grp < grps; grp++)
    {
        memcpy(mm.b, msg2 + os, 64);
        for (q = 0; q < 4; q++)
            efgh[q] = h[q];
        for (p = 0; p < 4; p++)
        {
            fctn = ff[p];
            rotn = rots[p];
            m = M[p];
            o = O[p];
            for (q = 0; q < 16; q++)
            {
                g = (m * q + o) % 16;
                f = efgh[1] + r(efgh[0] + fctn(efgh) + k[q + 16 * p] + mm.w[g], rotn[q % 4]);

                efgh[0] = efgh[3];
                efgh[3] = efgh[2];
                efgh[2] = efgh[1];
                efgh[1] = f;
            }
        }
        for (p = 0; p < 4; p++)
            h[p] += efgh[p];
        os += 64;
    }

    if (msg2)
        free(msg2);

    return h;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("%s", "please enter username and password.\n$ ./a.out [username] [password]\n");
        return 0;
    }

    p(argv[1], argv[2]);
    return 0;
}
