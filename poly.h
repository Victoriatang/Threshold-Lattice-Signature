#ifndef POLY_H_
#define POLY_H_

#include <stdint.h>
#include "params.h"
#include "config.h"
#include "ntt.h"
#include "fips202.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>


typedef struct {
  int32_t coeffs[N];
} poly;
typedef struct
{
  SecShare coeffshare[N];
} polyshare;

void poly_uniform(poly *a, ofstream &fout);
void poly_readuniform(poly *a,ifstream &fin);
void polyshare_read(polyshare *a,ifstream &fin,int index);
void poly_sharesecret(polyshare *a, ifstream &fin,int index, ofstream &fout);
void poly_sharetempsec(polyshare *a,ifstream &fin,int index);
void poly_reduce(poly *a);
void polyshare_reduce(polyshare *a);
void poly_caddq(poly *a);
void polyshare_caddq(polyshare *a);
void poly_freeze(poly *a);
void polyshare_freeze(polyshare *a);

void poly_add(poly *c, const poly *a, const poly *b);
void polyshare_add(polyshare *c,const polyshare *a,const polyshare *b);
//void poly_sub(poly *c, const poly *a, const poly *b);

//void poly_shiftl(poly *a);

void poly_ntt(poly *a);
void polyshare_ntt(polyshare *a);
void poly_invntt_tomont(poly *a);
void polyshare_invntt_tomont(polyshare *a);
void poly_pointwise_montgomery(poly *c, const poly *a, const poly *b);
void polyshare_pointwise_montgomery(polyshare *c,const poly*a, const polyshare *b);
void poly_challenge(poly *c, const uint8_t seed[SEEDBYTES]);
void polyw_packed(uint8_t *r,const poly *w);
void polyshare_shift(polyshare* a);
#endif
