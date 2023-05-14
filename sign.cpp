
#include "sign.h"

void sign1(ifstream &fin, ifstream &finbit,sharetempsec *y,const int index, signmessage1 *msg)
{
    polyvecl mat[K];
    sharetempsec z;
    polyvec_matrix_readuniform(mat,fin);
    polyvecl_sharetempsec(&y->y1,finbit,index);
    polyveck_sharetempsec(&y->y2,finbit,index);
    z.y1=y->y1;
    z.y2=y->y2;
    polysharevecl_shift(&z.y1);
    polyshareveck_shift(&z.y2);
    polysharevecl_ntt(&z.y1);
    polyshareveck_ntt(&z.y2);
    polyvec_matrix_pointwise_montgomery(&msg->wshare,mat,&z.y1);
   
    polyshareveck_reduce(&msg->wshare);
    polyshareveck_invntt_tomont(&msg->wshare);
    polyshareveck_add(&msg->wshare,&msg->wshare,&z.y2);   
    polyshareveck_freeze(&msg->wshare);
    
}
//open msg->wshare to get w
void sign2p(const uint8_t *m,unsigned int mlen,sharetempsec *y,ifstream &fin,const int index,
const polyveck *w,signshare *zshare, 
bitshares_mat *bitsmat,ifstream &finbit,poly *c, signshare *zzshare)
{
    polysharevecl s;
    polyshareveck e;
    keccak_state state;
    uint8_t r[K*POLYW_PACKEDBYTES];
    uint8_t seed[SEEDBYTES];
    polysharevecl_read(&s,fin,index);
    polyshareveck_read(&e,fin,index);
    /********
    generate challenge c*/
    polyveck_pack_w(r,w);
    shake256_init(&state);
    shake256_init(&state);
    shake256_absorb(&state,m,mlen);
    shake256_absorb(&state,r,K*POLYW_PACKEDBYTES);
    shake256_finalize(&state);
    shake256_squeeze(seed,SEEDBYTES,&state);
    poly_challenge(c,seed);


    /********
    compute zshare=yshare+sshare*c */
    poly_ntt(c);
    polysharevecl_ntt(&s);
    polysharevecl_poly_montgomery(&zshare->zlshare, c, &s);
    polysharevecl_reduce(&zshare->zlshare);
    polysharevecl_invntt_tomont(&zshare->zlshare);
    polysharevecl_add(&zshare->zlshare,&zshare->zlshare,&y->y1);
    polysharevecl_freeze(&zshare->zlshare);
    polyshareveck_ntt(&e);
    polyshareveck_pointwise_montgomery(&zshare->zkshare,c,&e);
    polyshareveck_reduce(&zshare->zkshare);
    polyshareveck_invntt_tomont(&zshare->zkshare);   
    polyshareveck_add(&zshare->zkshare,&zshare->zkshare,&y->y2);
    polyshareveck_freeze(&zshare->zkshare);
  //  cout<<zshare->zkshare.sharevec[3].coeffshare[200].share<<endl;
    zzshare->zlshare=zshare->zlshare;
    zzshare->zkshare=zshare->zkshare;
    //cout<<zzshare->zkshare.sharevec[3].coeffshare[200].share<<endl;
    /********
    intervaltest
    ********/
    for(int i=0;i<L+K;i++)
    {
      for(int j=0;j<N;j++)
      {
        if(i<L)
        {
          intervalt1p(zshare->zlshare.sharevec[i].coeffshare[j],
                     bitsmat->sharemat[i][j].bit,finbit);
        }
              
        else
          intervalt1p(zshare->zkshare.sharevec[i-L].coeffshare[j],
                     bitsmat->sharemat[i][j].bit,finbit);
      }
    }
}

void sign2(const uint8_t *m, unsigned int mlen,
sharetempsec *y,ifstream &fin,const int index,
const polyveck *w, signshare *zshare,blow_high_mat *blhmat,
ifstream &finbit)
{
    polysharevecl s;
    polyshareveck e;
    keccak_state state;
    poly c;
    uint8_t r[K*POLYW_PACKEDBYTES];
    uint8_t seed[SEEDBYTES];
    polysharevecl_read(&s,fin,index);
    polyshareveck_read(&e,fin,index);
    /********
    generate challenge c*/
    polyveck_pack_w(r,w);
    shake256_init(&state);
    shake256_init(&state);
    shake256_absorb(&state,m,mlen);
    shake256_absorb(&state,r,K*POLYW_PACKEDBYTES);
    shake256_finalize(&state);
    shake256_squeeze(seed,SEEDBYTES,&state);
    poly_challenge(&c,seed);


    /********
    compute zshare=yshare+sshare*c */
    poly_ntt(&c);
    polysharevecl_ntt(&s);
    polysharevecl_poly_montgomery(&zshare->zlshare, &c, &s);
    polysharevecl_reduce(&zshare->zlshare);
    polysharevecl_invntt_tomont(&zshare->zlshare);
    polysharevecl_add(&zshare->zlshare,&zshare->zlshare,&y->y1);
    polysharevecl_freeze(&zshare->zlshare);
    polyshareveck_ntt(&e);
    polyshareveck_pointwise_montgomery(&zshare->zkshare,&c,&e);
    polyshareveck_reduce(&zshare->zkshare);
    polyshareveck_invntt_tomont(&zshare->zkshare);   
    polyshareveck_add(&zshare->zkshare,&zshare->zkshare,&y->y2);
    polyshareveck_freeze(&zshare->zkshare);
    
}
//open each zkshare & zlshare to get c, here they are z plus a ranbom number.
//needcomp->blow=msg->blow 
/*void sign3(int32_t c[K+L][N],blow_high_mat *blhmat,lhbitsmat *boundlhbits,
multiplyrefmat *refSecShare,epsi_delta_sharemat *epdemat,
ifstream &fin,ifstream &fin1)
{
  cout<<"in this phase"<<endl;
  for(int i=0;i<L+K;i++)
  {
    for(int j=0;j<N;j++)
    {
      intervalt2(blhmat->bitsharemat[i][j].blow,blhmat->bitsharemat[i][j].bhigh,
      c[i][j],boundlow,boundhigh,boundlhbits->lhbmat[i][j].lowbits,
      boundlhbits->lhbmat[i][j].highbits,refSecShare->refmat[i][j].aalow,
      refSecShare->refmat[i][j].bblow,refSecShare->refmat[i][j].cclow,
      refSecShare->refmat[i][j].aahigh,refSecShare->refmat[i][j].bbhigh,
      refSecShare->refmat[i][j].cchigh,epdemat->matshare[i][j].epsilonsharelow,
      epdemat->matshare[i][j].deltasharelow,epdemat->matshare[i][j].epsilonsharehigh,
      epdemat->matshare[i][j].deltasharehigh,fin,fin1);
    }
  }
}
void sign4(multiplyrefmat *refSecShare,epsi_delta_mat *refintmat)
{
  for(int i=0;i<L+K;i++)
  {
    for(int j=0;j<N;j++)
    {
      intervalt3(refSecShare->refmat[i][j].aalow,refSecShare->refmat[i][j].bblow,
      refSecShare->refmat[i][j].cclow,refSecShare->refmat[i][j].aahigh,
      refSecShare->refmat[i][j].bbhigh,refSecShare->refmat[i][j].cchigh,
      refintmat->intmat[i][j].epsilonlow,refintmat->intmat[i][j].deltalow,
      refintmat->intmat[i][j].epsilonhigh,
      refintmat->intmat[i][j].deltahigh);
    }
  }
}

void sign5(lhbitsmat *boundlhbits,slow_high_mat *slhmat,
bitlow_high_mat *bitlhmat,blow_high_mat *blhmat,
sign5input_mat *inputmat,
ifstream &fin,ifstream &finb)
{
  for(int i=0;i<L+K;i++)
  {
    for(int j=0;j<N;j++)
    {
      intervalt4(boundlhbits->lhbmat[i][j].lowbits,
      boundlhbits->lhbmat[i][j].highbits,
      slhmat->smat[i][j].slow,slhmat->smat[i][j].shigh,
      bitlhmat->bitmat[i][j].bitlow,
      bitlhmat->bitmat[i][j].bithigh,
      blhmat->bitsharemat[i][j].blow,
      blhmat->bitsharemat[i][j].bhigh,
     inputmat->input5mat[i][j].mlow,
     inputmat->input5mat[i][j].mhigh,fin,finb);
    }
  }
}
void sign6(bitlow_high_mat *bitlhmat,multiply_tuple_mat *abc,
epsi_delta_sharepairmat *epsidelta, ifstream &fin)
{
  for(int i=0;i<L+K;i++)
  {
    for(int j=0;j<N;j++)
      intervalt5(boundlow,boundhigh,bitlhmat->bitmat[i][j].bitlow,
      bitlhmat->bitmat[i][j].bithigh,abc->abcmat[i][j].secsharea,
      abc->abcmat[i][j].secshareb,abc->abcmat[i][j].secsharec,
      epsidelta->pairmat[i][j].epsilonshare,
      epsidelta->pairmat[i][j].deltashare,fin);
  }
}
void sign7(int32_t c[K+L][N],multiply_tuple_mat *abc,
epsi_delta_pairmat* intmat)
{
  for(int i=0;i<L+K;i++)
  {
    for(int j=0;j<N;j++)
    {
      intervalt6(c[i][j],boundlow,boundhigh,abc->abcmat[i][j].secsharea,
      abc->abcmat[i][j].secshareb,abc->abcmat[i][j].secsharec,
      intmat->intpairmat[i][j].epsilon,intmat->intpairmat[i][j].delta);
    }
  }
}*/