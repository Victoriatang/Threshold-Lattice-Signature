#ifndef BITLTC1_H_
#define BITLTC1_H_

#include "config.h"
#include "params.h"
#include "premul.h"
void Bitltc1(int32_t a, SecShare b[comp_bitsNum],SecShare aa[comp_bitsNum],SecShare bb[comp_bitsNum],SecShare cc[comp_bitsNum],
	SecShare epsilonshare[comp_bitsNum],SecShare deltashare[comp_bitsNum],ifstream &fin,ifstream &fin1);
//the input of the problem is a and b[comp_bitsNum], the output is abits[comp_bitsNum],b[comp_bitsNum]，b[i]=ai+bi-2ai*bi+1(reorder). 
//(d,aa,bb,cc,epsilonshare,deltashare fin,fin1 are used for prmult) 
// b0 b1 b2 ..... bcomp_bitsNum-1
// dcomp_bitsNum-1 d21  ..... d0
//epsilonshare[comp_bitsNum] is opened to be epsilon[comp_bitsNum]
void Bitltc2(SecShare aa[comp_bitsNum],SecShare bb[comp_bitsNum],SecShare cc[comp_bitsNum],int32_t epsilon[comp_bitsNum],int32_t delta[comp_bitsNum]);
// the result is aa[comp_bitsNum], which is opened to be m[comp_bitsNum]
void Bitltc3(int32_t a,SecShare &s, SecShare &bit,SecShare b[comp_bitsNum],int32_t m[comp_bitsNum],
	ifstream &fin,ifstream &finb);
//b,m,fin are used for prmult, the result is p[comp_bitsNum], the output is s,bit 
// finb is used for reading random bit SecShare bit
void Bitltc3minus(int32_t a,SecShare &s, SecShare &bit,SecShare b[comp_bitsNum],int32_t m[comp_bitsNum],
	ifstream &fin,ifstream &finb);
void Bitltc4(int32_t c, SecShare &bit);
//s is opened to be int c, the result is bit.


#endif
