#ifndef SIGN_H_
#define SIGN_H_

#include "polyvec.h"
#include "intervaltest.h"
#include "config.h"
#include "params.h"
typedef struct{
    polysharevecl y1;
    polyshareveck y2;
} sharetempsec;
typedef struct{
    polysharevecl s;
    polyshareveck e;
} sharesk;
typedef struct{
    polyshareveck wshare;
} signmessage1;

typedef struct{
    polysharevecl zlshare;
    polyshareveck zkshare;
} signshare;
typedef struct{
    SecShare blow[comp_bitsNum];
    SecShare bhigh[comp_bitsNum];
} blow_high;
typedef struct{
    blow_high bitsharemat[L+K][N];
} blow_high_mat; //need to be compared
typedef struct{
    SecShare aalow[comp_bitsNum];
    SecShare bblow[comp_bitsNum];
    SecShare cclow[comp_bitsNum];
    SecShare aahigh[comp_bitsNum];
    SecShare bbhigh[comp_bitsNum];
    SecShare cchigh[comp_bitsNum];
} multiplyref;
typedef struct{
        SecShare epsilonsharelow[comp_bitsNum];
    SecShare deltasharelow[comp_bitsNum];
	SecShare epsilonsharehigh[comp_bitsNum];
    SecShare deltasharehigh[comp_bitsNum];
}epsi_delta_share;
typedef struct{
    int32_t epsilonlow[comp_bitsNum];
    int32_t deltalow[comp_bitsNum];
    int32_t epsilonhigh[comp_bitsNum];
    int32_t deltahigh[comp_bitsNum];
}epsi_delta;
typedef struct{
    multiplyref refmat[L+K][N];
} multiplyrefmat;
typedef struct
{
    epsi_delta_share matshare[L+K][N];
}epsi_delta_sharemat;
typedef struct{
    epsi_delta intmat[L+K][N];
}epsi_delta_mat;
typedef struct{
    int32_t lowbits[comp_bitsNum];
    int32_t highbits[comp_bitsNum];
}lhbits;
typedef struct{
    lhbits lhbmat[L+K][N];
}lhbitsmat;  // bits of bound
typedef struct{
    SecShare slow;
    SecShare shigh;
}slow_high;
typedef struct{
    slow_high smat[L+K][N];
}slow_high_mat;
typedef struct{
    SecShare bitlow;
    SecShare bithigh;
}bitlow_high; 
typedef struct{
    bitlow_high bitmat[L+K][N];
}bitlow_high_mat; //bit used in intervalt4
typedef struct{
    int32_t mlow[comp_bitsNum];
    int32_t mhigh[comp_bitsNum];
}sign5input;
typedef struct{
    sign5input input5mat[L+K][N];
}sign5input_mat;
typedef struct{
    SecShare secsharea;
    SecShare secshareb;
    SecShare secsharec;
} multiply_tuple;
typedef struct{
    multiply_tuple abcmat[L+K][N];
}multiply_tuple_mat;
typedef struct{
    SecShare epsilonshare;
    SecShare deltashare;
}epsi_delta_sharepair;
typedef struct{
    epsi_delta_sharepair pairmat[L+K][N];
}epsi_delta_sharepairmat;
typedef struct{
    int32_t epsilon;
    int32_t delta;
}epsi_delta_pair;
typedef struct{
    epsi_delta_pair intpairmat[L+K][N];
}epsi_delta_pairmat;

/********simple version
*********************/
typedef struct{
    SecShare bit[comp_bitsNum];
} bitshares;
typedef struct{
    bitshares sharemat[L+K][N];
}bitshares_mat;



void sign1(ifstream &fin,ifstream &finbit,
            sharetempsec *y,int index,
            signmessage1 *msg);
void sign2p(const uint8_t *m,unsigned int mlen,sharetempsec *y,ifstream &fin,
const int index,const polyveck *w,signshare *zshare, 
bitshares_mat *bitsmat,ifstream &finbit,poly *c, signshare *zzshare);
void sign2(const uint8_t *m, unsigned int mlen,
sharetempsec *y,ifstream &fin,const int index,
const polyveck *w, signshare *zshare,
blow_high_mat *blhmat,
ifstream &finbit);
/*void sign3(int32_t c[K+L][N],blow_high_mat *blhmat,lhbitsmat *boundlhbits,
multiplyrefmat *refSecShare,epsi_delta_sharemat *epdemat,
ifstream &fin,ifstream &fin1);
void sign4(multiplyrefmat *refSecShare,epsi_delta_mat *refintmat);
void sign5(lhbitsmat *boundlhbits,slow_high_mat *slhmat,
bitlow_high_mat *bitlhmat,blow_high_mat *blhmat,
sign5input_mat *inputmat,
ifstream &fin,ifstream &finb);
void sign6(bitlow_high_mat *bitlhmat,multiply_tuple_mat *abc,
epsi_delta_sharepairmat *epsidelta, ifstream &fin);
void sign7(int32_t c[K+L][N],multiply_tuple_mat *abc,
epsi_delta_pairmat* intmat);*/
#endif