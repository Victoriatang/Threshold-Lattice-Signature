#ifndef POLYVEC_H_
#define POLYVEC_H_

#include <stdint.h>
#include "params.h"
#include "poly.h"
#include "config.h"
#include <fstream>

/* Vectors of polynomials of length L */
typedef struct {
  poly vec[L];
} polyvecl;
typedef struct{
  polyshare sharevec[L];
} polysharevecl;
typedef struct {
  poly vec[K];
} polyveck;
typedef struct 
{
  polyshare sharevec[K];
} polyshareveck;
void polyvec_matrix(polyvecl mat[K], ofstream &fout);
void polyvec_matrix_pointwise_montgomery(polyshareveck *t, const polyvecl mat[K], const polysharevecl *v);
void polyvec_matrix_readuniform(polyvecl mat[K],ifstream &fin);
void polyvecl_sharesecret(polysharevecl *s,ifstream &fin,int index,ofstream &fout);
void polyvecl_sharetempsec(polysharevecl *y1,ifstream &fin,int index);
void polysharevecl_reduce(polysharevecl *v);
void polysharevecl_read(polysharevecl *s, ifstream &fin,int index);
void polysharevecl_freeze(polysharevecl *v);
void polysharevecl_add(polysharevecl *w, const polysharevecl *u, const polysharevecl *v);
void polyvecl_ntt(polyvecl *v);
void polysharevecl_ntt(polysharevecl *v);
void polyvecl_invntt_tomont(polyvecl *v);
void polysharevecl_invntt_tomont(polysharevecl *v);
void polysharevecl_poly_montgomery(polysharevecl *r, const poly *a, const polysharevecl *v);
void polyvecl_pointwise_acc_montgomery(polyshare *w,
                                       const polyvecl *u,
                                       const polysharevecl *v);

/* Vectors of polynomials of length K */

void polyveck_sharesecret(polyshareveck *s,ifstream &fin,int index,ofstream &fout);
void polyveck_sharetempsec(polyshareveck *y1,ifstream &fin,int index);
void polyshareveck_reduce(polyshareveck *v);
void polyshareveck_read(polyshareveck *s, ifstream &fin,int index);
void polyshareveck_caddq(polyshareveck *v) ;
void polyshareveck_freeze(polyshareveck *v);
void polyshareveck_add(polyshareveck *w, const polyshareveck *u, const polyshareveck *v);
void polyshareveck_ntt(polyshareveck *v);
void polyshareveck_invntt_tomont(polyshareveck *v);
void polyshareveck_pointwise_montgomery(polyshareveck *r, const poly *a, const polyshareveck *v);
void polyveck_pack_w(uint8_t r[K*POLYW_PACKEDBYTES],const polyveck *w);
void polyvecl_openshare(polyvecl *z,const polysharevecl *x,const polysharevecl *y);
void polyveck_openshare(polyveck *z,const polyshareveck *x,const polyshareveck *y);
void polyveck_pointwise_montgomery(polyveck *c,poly*a, polyveck *b);
void polyveck_ntt(polyveck *a);
void polyveck_invntt_tomont(polyveck *a);
void polyveck_reduce(polyveck *a);
void polysharevecl_shift(polysharevecl *a);
void polyshareveck_shift(polyshareveck *a);
#endif
