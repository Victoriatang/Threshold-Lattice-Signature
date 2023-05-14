#ifndef CONFIG_H_
#define CONFIG_H_
 


#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include "params.h"
using namespace std;

class SecShare
{
public:
	int index;
	int32_t share;
	int32_t MACshare;
	int32_t delta;
	void setSecShare(int i,int32_t x, int32_t y,int32_t z);
};
int32_t module(int64_t a);
void Secaddcon(SecShare &a,int32_t e);
void Secadd(SecShare &a,SecShare b);
void Secmulticon(SecShare &a, int32_t e);
void multiply1(SecShare x,SecShare y,SecShare &a,SecShare &b,SecShare &c,SecShare &epsilonshare,
	SecShare &deltashare,ifstream &fin);
void multiply2(SecShare &a,SecShare &b,SecShare &c,int32_t epsilon,int32_t delta);
#endif

