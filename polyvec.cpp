
#include "polyvec.h"


/*************************************************
* Name:        expand_mat
*
* Description: Implementation of ExpandA. Generates matrix A with uniformly
*              random coefficients a_{i,j} by performing rejection
*              sampling on the output stream of SHAKE128(rho|j|i)
*              or AES256CTR(rho,j|i).
*
* Arguments:   - polyvecl mat[K]: output matrix
*              - const uint8_t rho[]: byte array containing seed rho
**************************************************/
//generate A K*L
void polyvec_matrix(polyvecl mat[K], ofstream &fout) {
  unsigned int i, j;
  

  for(i = 0; i < K; ++i)
  {
    for(j = 0; j < L; ++j)
    {
      poly_uniform(&mat[i].vec[j],fout);     
    }
    
  }  
}

//A*s k rows
void polyvec_matrix_pointwise_montgomery(polyshareveck *t, const polyvecl mat[K], const polysharevecl *v) {
  unsigned int i;

  for(i = 0; i < K; ++i)
    polyvecl_pointwise_acc_montgomery(&t->sharevec[i], &mat[i], v);
}
void polyvec_matrix_readuniform(polyvecl mat[K],ifstream &fin)
{
  for(int i=0;i<K;i++)
  {
    for(int j=0;j<L;j++)
    {
      poly_readuniform(&mat[i].vec[j],fin);
    }
  }
  
}

/**************************************************************/
/************ Vectors of polynomials of length L **************/
/**************************************************************/
void polyvecl_sharesecret(polysharevecl *s,ifstream &fin,int index,ofstream &fout)
{
  unsigned int i;
  for(i=0;i<L;i++)
  {
    poly_sharesecret(&s->sharevec[i],fin,index,fout);
  }
}
void polyvecl_sharetempsec(polysharevecl *y1,ifstream &fin,int index)
{
 
  for(int i=0;i<L;i++)
  {
    poly_sharetempsec(&y1->sharevec[i],fin,index);
  }
}

void polysharevecl_reduce(polysharevecl *v) {
  unsigned int i;

  for(i = 0; i < L; ++i)
    polyshare_reduce(&v->sharevec[i]);
}
void polysharevecl_read(polysharevecl *s, ifstream &fin,int index)
{
  for(int i=0;i<L;i++)
  {
    polyshare_read(&s->sharevec[i],fin,index);
  }
}

/*************************************************
* Name:        polyvecl_freeze
*
* Description: Reduce coefficients of polynomials in vector of length L
*              to standard representatives.
*
* Arguments:   - polyvecl *v: pointer to input/output vector
**************************************************/
void polysharevecl_freeze(polysharevecl *v) {
  unsigned int i;

  for(i = 0; i < L; ++i)
    polyshare_freeze(&v->sharevec[i]);
}

/*************************************************
* Name:        polyvecl_add
*
* Description: Add vectors of polynomials of length L.
*              No modular reduction is performed.
*
* Arguments:   - polyvecl *w: pointer to output vector
*              - const polyvecl *u: pointer to first summand
*              - const polyvecl *v: pointer to second summand
**************************************************/
void polysharevecl_add(polysharevecl *w, const polysharevecl *u, const polysharevecl *v) {
  unsigned int i;

  for(i = 0; i < L; ++i)
    polyshare_add(&w->sharevec[i], &u->sharevec[i], &v->sharevec[i]);
}

/*************************************************
* Name:        polyvecl_ntt
*
* Description: Forward NTT of all polynomials in vector of length L. Output
*              coefficients can be up to 16*Q larger than input coefficients.
*
* Arguments:   - polyvecl *v: pointer to input/output vector
**************************************************/
void polyvecl_ntt(polyvecl *v)
{
  unsigned int i;
  for(i=0;i<L;i++)
    poly_ntt(&v->vec[i]);
}
void polysharevecl_ntt(polysharevecl *v) {
  unsigned int i;

  for(i = 0; i < L; ++i)
    polyshare_ntt(&v->sharevec[i]);
}

void polyvecl_invntt_tomont(polyvecl *v) {
  unsigned int i;

  for(i = 0; i < L; ++i)
    poly_invntt_tomont(&v->vec[i]);
}
//ntt(s,y1)
void polysharevecl_invntt_tomont(polysharevecl *v) {
  unsigned int i;

  for(i = 0; i < L; ++i)
    polyshare_invntt_tomont(&v->sharevec[i]);
}
//c*s
void polysharevecl_poly_montgomery(polysharevecl *r, const poly *a, const polysharevecl *v) {
  unsigned int i;

  for(i = 0; i < L; ++i)
    polyshare_pointwise_montgomery(&r->sharevec[i], a, &v->sharevec[i]);
}

/*************************************************
* Name:        polyvecl_pointwise_acc_montgomery
*
* Description: Pointwise multiply vectors of polynomials of length L, multiply
*              resulting vector by 2^{-32} and add (accumulate) polynomials
*              in it. Input/output vectors are in NTT domain representation.
*
* Arguments:   - poly *w: output polynomial
*              - const polyvecl *u: pointer to first input vector
*              - const polyvecl *v: pointer to second input vector
**************************************************/
//each row of A*s 
void polyvecl_pointwise_acc_montgomery(polyshare *w,
                                       const polyvecl *u,
                                       const polysharevecl *v)
{
  unsigned int i;
  polyshare t;

  polyshare_pointwise_montgomery(w, &u->vec[0], &v->sharevec[0]);
  for(i = 1; i < L; ++i) {
    polyshare_pointwise_montgomery(&t, &u->vec[i], &v->sharevec[i]);
    polyshare_add(w, w, &t);
  }
}



/**************************************************************/
/************ Vectors of polynomials of length K **************/
/**************************************************************/

void polyveck_sharesecret(polyshareveck *s,ifstream &fin,int index,ofstream &fout)
{
  unsigned int i;
  for(i=0;i<K;i++)
  {
    poly_sharesecret(&s->sharevec[i],fin,index,fout);
  }
}
void polyveck_sharetempsec(polyshareveck *y1,ifstream &fin,int index)
{
  
  for(int i=0;i<K;i++)
  {
    poly_sharetempsec(&y1->sharevec[i],fin,index);
  }
}
/*************************************************
* Name:        polyveck_reduce
*
* Description: Reduce coefficients of polynomials in vector of length K
*              to representatives in [-6283009,6283007].
*
* Arguments:   - polyveck *v: pointer to input/output vector
**************************************************/
void polyshareveck_reduce(polyshareveck *v) {
  unsigned int i;

  for(i = 0; i < K; ++i)
    polyshare_reduce(&v->sharevec[i]);
}
void polyshareveck_read(polyshareveck *s, ifstream &fin,int index)
{
  for(int i=0;i<K;i++)
  {
    polyshare_read(&s->sharevec[i],fin,index);
  }
}



/*************************************************
* Name:        polyveck_caddq
*
* Description: For all coefficients of polynomials in vector of length K
*              add Q if coefficient is negative.
*
* Arguments:   - polyveck *v: pointer to input/output vector
**************************************************/
void polyshareveck_caddq(polyshareveck *v) {
  unsigned int i;

  for(i = 0; i < K; ++i)
    polyshare_caddq(&v->sharevec[i]);
}

/*************************************************
* Name:        polyveck_freeze
*
* Description: Reduce coefficients of polynomials in vector of length K
*              to standard representatives.
*
* Arguments:   - polyveck *v: pointer to input/output vector
**************************************************/
void polyshareveck_freeze(polyshareveck *v)  {
  unsigned int i;

  for(i = 0; i < K; ++i)
    polyshare_freeze(&v->sharevec[i]);
}

/*************************************************
* Name:        polyveck_add
*
* Description: Add vectors of polynomials of length K.
*              No modular reduction is performed.
*
* Arguments:   - polyveck *w: pointer to output vector
*              - const polyveck *u: pointer to first summand
*              - const polyveck *v: pointer to second summand
**************************************************/
void polyshareveck_add(polyshareveck *w, const polyshareveck *u, const polyshareveck *v) {
  unsigned int i;

  for(i = 0; i < K; ++i)
    polyshare_add(&w->sharevec[i], &u->sharevec[i], &v->sharevec[i]);
}


/*************************************************
* Name:        polyveck_ntt
*
* Description: Forward NTT of all polynomials in vector of length K. Output
*              coefficients can be up to 16*Q larger than input coefficients.
*
* Arguments:   - polyveck *v: pointer to input/output vector
**************************************************/
void polyshareveck_ntt(polyshareveck *v) {
  unsigned int i;

  for(i = 0; i < K; ++i)
    polyshare_ntt(&v->sharevec[i]);
}

/*************************************************
* Name:        polyveck_invntt_tomont
*
* Description: Inverse NTT and multiplication by 2^{32} of polynomials
*              in vector of length K. Input coefficients need to be less
*              than 2*Q.
*
* Arguments:   - polyveck *v: pointer to input/output vector
**************************************************/
void polyshareveck_invntt_tomont(polyshareveck *v) {
  unsigned int i;

  for(i = 0; i < K; ++i)
    polyshare_invntt_tomont(&v->sharevec[i]);
}

void polyshareveck_pointwise_montgomery(polyshareveck *r, const poly *a, const polyshareveck *v) {
  unsigned int i;

  for(i = 0; i < K; ++i)
    polyshare_pointwise_montgomery(&r->sharevec[i], a, &v->sharevec[i]);
}
void polyveck_pack_w(uint8_t r[K*POLYW_PACKEDBYTES],const polyveck *w)
{
  for(int i=0;i<K;i++)
  {
    polyw_packed(&r[i*POLYW_PACKEDBYTES],&w->vec[i]);
  }
}

void polyvecl_openshare(polyvecl *z,const polysharevecl *x,const polysharevecl *y)
{
  for(int i=0;i<L;i++)
  {
    for(int j=0;j<N;j++)
      z->vec[i].coeffs[j]=freeze(x->sharevec[i].coeffshare[j].share+
                          y->sharevec[i].coeffshare[j].share);
  }
}
void polyveck_openshare(polyveck *z,const polyshareveck *x,const polyshareveck *y)
{
  for(int i=0;i<K;i++)
  {
    for(int j=0;j<N;j++)
      z->vec[i].coeffs[j]=freeze(x->sharevec[i].coeffshare[j].share+
                          y->sharevec[i].coeffshare[j].share);
  }
}
void polyveck_pointwise_montgomery(polyveck *c,poly*a, polyveck *b)
{
  for(int i=0;i<K;i++)
    poly_pointwise_montgomery(&c->vec[i],a,&b->vec[i]);
}
void polyveck_ntt(polyveck *a)
{
  for(int i=0;i<K;i++)
    poly_ntt(&a->vec[i]);
}
void polyveck_invntt_tomont(polyveck *a)
{
  for(int i=0;i<K;i++)
    poly_invntt_tomont(&a->vec[i]);
}
void polyveck_reduce(polyveck *a)
{
  for(int i=0;i<K;i++)
    poly_reduce(&a->vec[i]);
}
void polysharevecl_shift(polysharevecl *a)
{
  for(int i=0;i<L;i++)
  {
    polyshare_shift(&a->sharevec[i]);
  }
}
void polyshareveck_shift(polyshareveck *a)
{
  for(int i=0;i<K;i++)
  {
    polyshare_shift(&a->sharevec[i]);
  }
}