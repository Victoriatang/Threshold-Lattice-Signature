

#include "poly.h"


/*#ifdef DBENCH
#include "test/cpucycles.h"
extern const uint64_t timing_overhead;
extern uint64_t *tred, *tadd, *tmul, *tround, *tsample, *tpack;
#define DBENCH_START() uint64_t time = cpucycles()
#define DBENCH_STOP(t) t += cpucycles() - time - timing_overhead
#else
#define DBENCH_START()
#define DBENCH_STOP(t)
#endif*/
void poly_uniform(poly *a,ofstream &fout)
{
  srand((int)time(NULL));
  unsigned int i;
  for(i=0;i<N;i++)
  {

    a->coeffs[i]=rand()%Q;
    fout<<a->coeffs[i]<<endl;
  }
}

void poly_readuniform(poly *a,ifstream &fin)
{
  for(int i=0;i<N;i++)
  {
    fin>>a->coeffs[i];
  }
}
void polyshare_read(polyshare *a,ifstream &fin,int index)
{
  stringstream is;
  string data;
  int32_t str[3];
  for(int i=0;i<N;i++)
  {
    if(fin.eof())
    {
      fin.clear();
      fin.seekg(0,ios::beg);
    }
    getline(fin,data);
    is.clear();
    is.str("");
    is.str(data);
    is>>str[0]>>str[1]>>str[2];
    a->coeffshare[i].setSecShare(index,str[0],str[1],str[2]);
  }
}

void poly_sharesecret(polyshare *a, ifstream &fin,int index, ofstream &fout)
{
  unsigned int i,j;
  string data;
  stringstream is;
  int32_t str[3]; 
  SecShare bit;
  int32_t temp;
  int32_t bound=1<<etabitsNum;
  int32_t shift=1-bound/2;
  for(i=0;i<N;i++)
  {
    a->coeffshare[i].setSecShare(index,0,0,0);
    for(j=0;j<etabitsNum;j++)
    {
      temp=1<<j;
      if(fin.eof())
      {
        fin.clear();
        fin.seekg(0,ios::beg);
      }
      getline(fin,data);
      is.clear();
      is.str("");
      is.str(data);
      is>>str[0]>>str[1]>>str[2];
      bit.setSecShare(index,str[0],str[1],str[2]);
      Secmulticon(bit,temp);  //bit*2^j    
      Secadd(a->coeffshare[i],bit);
    }
    
    Secaddcon(a->coeffshare[i],shift);
    fout<<a->coeffshare[i].share<<'\t'<<a->coeffshare[i].MACshare<<'\t'<<a->coeffshare[i].delta<<endl;
  }
}
void poly_sharetempsec(polyshare *a,ifstream &fin,int index)
{
   unsigned int i,j;
  string data;
  stringstream is;
  int32_t str[3]; 
  SecShare bit;
  int32_t temp;
 // int32_t bound=1<<GammabitsNum;
//  int32_t shift=1-bound/2;
  for(i=0;i<N;i++)
  {
    a->coeffshare[i].setSecShare(index,0,0,0);
    for(j=0;j<GammabitsNum;j++)
    {
      temp=1<<j;
      if(fin.eof())
      {
        //cout<<i<<'\t'<<"Read Done!!!!!!!!!!!!"<<endl;
        fin.clear();
        fin.seekg(0,ios::beg);
      }
      getline(fin,data);
      is.clear();
      is.str("");
      is.str(data);
      is>>str[0]>>str[1]>>str[2];
      bit.setSecShare(index,str[0],str[1],str[2]);
      Secmulticon(bit,temp);  //bit*2^j    
      Secadd(a->coeffshare[i],bit);
      
    } 
    //cout<<a->coeffshare[i].share<<endl; 
   // Secaddcon(a->coeffshare[i],shift);
  }
}
/*************************************************
* Name:        poly_reduce
*
* Description: Inplace reduction of all coefficients of polynomial to
*              representative in [-6283009,6283007].
*
* Arguments:   - poly *a: pointer to input/output polynomial
**************************************************/
void poly_reduce(poly *a) {
  unsigned int i;
 // DBENCH_START();

  for(i = 0; i < N; ++i)
    a->coeffs[i] = reduce32(a->coeffs[i]);

//  DBENCH_STOP(*tred);
}
void polyshare_reduce(polyshare *a) {
  
 // DBENCH_START();
  for(int i=0;i<N;i++)
  {
    a->coeffshare[i].share=reduce32(a->coeffshare[i].share);
    a->coeffshare[i].MACshare=reduce32(a->coeffshare[i].MACshare);
    a->coeffshare[i].delta=reduce32(a->coeffshare[i].delta);
  }
//  DBENCH_STOP(*tred);
}
/*************************************************
* Name:        poly_caddq
*
* Description: For all coefficients of in/out polynomial add Q if
*              coefficient is negative.
*
* Arguments:   - poly *a: pointer to input/output polynomial
**************************************************/
void poly_caddq(poly *a) {
  unsigned int i;
//  DBENCH_START();

  for(i = 0; i < N; ++i)
    a->coeffs[i] = caddq(a->coeffs[i]);

//  DBENCH_STOP(*tred);
}
void polyshare_caddq(polyshare *a)
{
  for(int i=0;i<N;i++)
  {
    a->coeffshare[i].share=caddq(a->coeffshare[i].share);
    a->coeffshare[i].MACshare=caddq(a->coeffshare[i].MACshare);
    a->coeffshare[i].delta=caddq(a->coeffshare[i].delta);
  }
}
/*************************************************
* Name:        poly_freeze
*
* Description: Inplace reduction of all coefficients of polynomial to
*              standard representatives.
*
* Arguments:   - poly *a: pointer to input/output polynomial
**************************************************/
void poly_freeze(poly *a) {
  unsigned int i;
  //DBENCH_START();

  for(i = 0; i < N; ++i)
    a->coeffs[i] = freeze(a->coeffs[i]);

 // DBENCH_STOP(*tred);
}
void polyshare_freeze(polyshare *a) {
  unsigned int i;
  //DBENCH_START();

  for(i = 0; i < N; ++i)
  { 
    a->coeffshare[i].share = freeze(a->coeffshare[i].share);
    a->coeffshare[i].MACshare=freeze(a->coeffshare[i].MACshare);
    a->coeffshare[i].delta=freeze(a->coeffshare[i].delta);
  }

 // DBENCH_STOP(*tred);
}
/*************************************************
* Name:        poly_add
*
* Description: Add polynomials with modular reduction.
*
* Arguments:   - poly *c: pointer to output polynomial
*              - const poly *a: pointer to first summand
*              - const poly *b: pointer to second summand
**************************************************/
void poly_add(poly *c, const poly *a, const poly *b)  {
 
  for(int i = 0; i < N; i++)
    c->coeffs[i] = a->coeffs[i] + b->coeffs[i];
  //poly_freeze(c);

}
void polyshare_add(polyshare *c,const polyshare *a,const polyshare *b)
{
  for(int i=0;i<N;i++)
  {
    c->coeffshare[i].share=a->coeffshare[i].share+b->coeffshare[i].share;
    c->coeffshare[i].MACshare=a->coeffshare[i].MACshare+b->coeffshare[i].MACshare;
    c->coeffshare[i].delta=a->coeffshare[i].delta+b->coeffshare[i].delta;
  }
}




/*************************************************
* Name:        poly_ntt
*
* Description: Inplace forward NTT. Coefficients can grow by
*              8*Q in absolute value.
*
* Arguments:   - poly *a: pointer to input/output polynomial
**************************************************/
void poly_ntt(poly *a) {
  

  ntt(a->coeffs);

}
void polyshare_ntt(polyshare *a)
{
  int32_t ashare[N],aMACshare[N],adelta[N];
  int index=a->coeffshare[0].index;
  for(int i=0;i<N;i++)
  {
    ashare[i]=a->coeffshare[i].share;
    aMACshare[i]=a->coeffshare[i].MACshare;
    adelta[i]=a->coeffshare[i].delta;
  }
  ntt(ashare);
  ntt(aMACshare);
  ntt(adelta);
  for(int i=0;i<N;i++)
  {
    a->coeffshare[i].setSecShare(index,ashare[i],aMACshare[i],adelta[i]);
  }
}
/*************************************************
* Name:        poly_invntt_tomont
*
* Description: Inplace inverse NTT and multiplication by 2^{32}.
*              Input coefficients need to be less than Q in absolute
*              value and output coefficients are again bounded by Q.
*
* Arguments:   - poly *a: pointer to input/output polynomial
**************************************************/
void poly_invntt_tomont(poly *a) {
  //DBENCH_START();

  invntt_tomont(a->coeffs);

 // DBENCH_STOP(*tmul);
}
void polyshare_invntt_tomont(polyshare *a)
{
  int32_t ashare[N],aMACshare[N],adelta[N];
  int index=a->coeffshare[0].index;
  for(int i=0;i<N;i++)
  {
    ashare[i]=a->coeffshare[i].share;
    aMACshare[i]=a->coeffshare[i].MACshare;
    adelta[i]=a->coeffshare[i].delta;
  }
  invntt_tomont(ashare);
  invntt_tomont(aMACshare);
  invntt_tomont(adelta);
  for(int i=0;i<N;i++)
  {
    a->coeffshare[i].setSecShare(index,ashare[i],aMACshare[i],adelta[i]);
  }
}

/*************************************************
* Name:        poly_pointwise_montgomery
*
* Description: Pointwise multiplication of polynomials in NTT domain
*              representation and multiplication of resulting polynomial
*              by 2^{-32}.
*
* Arguments:   - poly *c: pointer to output polynomial
*              - const poly *a: pointer to first input polynomial
*              - const poly *b: pointer to second input polynomial
**************************************************/
void poly_pointwise_montgomery(poly *c, const poly *a, const poly *b) {
  unsigned int i;
//  DBENCH_START();

  for(i = 0; i < N; ++i)
    c->coeffs[i] = montgomery_reduce((int64_t)a->coeffs[i] * b->coeffs[i]);

  //DBENCH_STOP(*tmul);
}

void polyshare_pointwise_montgomery(polyshare *c,const poly*a, const polyshare *b)
{
  unsigned int i;
  int index=b->coeffshare[0].index;
  int32_t cshare,cMACshare,cdelta;
  for(i=0;i<N;i++)
  {
    cshare=montgomery_reduce((int64_t)a->coeffs[i]*b->coeffshare[i].share);
    cMACshare=montgomery_reduce((int64_t)a->coeffs[i]*b->coeffshare[i].MACshare);
    cdelta=montgomery_reduce((int64_t)a->coeffs[i]*b->coeffshare[i].delta);
    c->coeffshare[i].setSecShare(index,cshare,cMACshare,cdelta);
  }
}

/*************************************************
* Name:        challenge
*
* Description: Implementation of H. Samples polynomial with TAU nonzero
*              coefficients in {-1,1} using the output stream of
*              SHAKE256(seed).
*
* Arguments:   - poly *c: pointer to output polynomial
*              - const uint8_t mu[]: byte array containing seed of length SEEDBYTES
**************************************************/
void poly_challenge(poly *c, const uint8_t seed[SEEDBYTES]) {
  unsigned int i, b, pos;
  uint64_t signs;
  uint8_t buf[SHAKE256_RATE];
  keccak_state state;

  shake256_init(&state);
  shake256_absorb(&state, seed, SEEDBYTES);
  shake256_finalize(&state);
  shake256_squeezeblocks(buf, 1, &state);

  signs = 0;
  for(i = 0; i < 8; ++i)
    signs |= (uint64_t)buf[i] << 8*i;
  pos = 8;

  for(i = 0; i < N; ++i)
    c->coeffs[i] = 0;
  for(i = N-TAU; i < N; ++i) {
    do {
      if(pos >= SHAKE256_RATE) {
        shake256_squeezeblocks(buf, 1, &state);
        pos = 0;
      }

      b = buf[pos++];
    } while(b > i);

    c->coeffs[i] = c->coeffs[b];
    c->coeffs[b] = 1 - 2*(signs & 1);
    signs >>= 1;
  }
}
void polyw_packed(uint8_t *r,const poly *w)
{
  for(int i=0;i<N;i++)
  {
    r[3*i+0]=w->coeffs[i];
    r[3*i+1]=w->coeffs[i]>>8;
    r[3*i+2]=w->coeffs[i]>>16;
  }
}
void polyshare_shift(polyshare* a)
{
  int32_t bound=1<<GammabitsNum;
  int32_t shift=1-bound/2;
  for(int i=0;i<N;i++)
    Secaddcon(a->coeffshare[i],shift);
}




