#ifndef PREMUL_H_
#define PREMUL_H_

#include "config.h"
#include "params.h"
void premult1(SecShare a[comp_bitsNum],SecShare aa[comp_bitsNum],SecShare bb[comp_bitsNum],SecShare cc[comp_bitsNum],SecShare epsilonshare[comp_bitsNum],SecShare deltashare[comp_bitsNum],
ifstream &fin,ifstream &fin1);
void premult2(SecShare aa[comp_bitsNum],SecShare bb[comp_bitsNum],SecShare cc[comp_bitsNum],int32_t epsilon[comp_bitsNum],int32_t delta[comp_bitsNum]);
void premult3(SecShare a[comp_bitsNum],SecShare p[comp_bitsNum],int32_t m[comp_bitsNum],ifstream &fin);

#endif