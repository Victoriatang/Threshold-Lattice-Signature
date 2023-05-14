#include "config.h"
#include "randbit.h"
#include "premul.h"
#include "BitLTC1.h"
#include "intervaltest.h"
#include <cmath>

//#include <iostream>
//using namespace std;
/*bool isvalid(int64_t share1,int64_t share2,int64_t Macshare1, int64_t Macshare2,int64_t delta)
{
	int64_t alpha=3993562;
	int64_t share=share1+share2;
	module(share);
	cout<<share<<endl;
	int64_t MACshare=Macshare1+Macshare2;
	module(MACshare);
	int64_t k=alpha*(share+delta);
	module(k);
	cout<<"Check is "<<MACshare<<'\t'<<k<<endl;
	if(MACshare==k)
	{
		return true;

	}
	return false;

}*/

int main(){
	SecShare blow1[23],blow2[23];
	ifstream finb1,finb2;
	ifstream finr1,finr2;
	ifstream fin1,fin2,fin3,fin4,fin5,fin6;
	finb1.open("randbit0.txt",ios::in);
	finb2.open("randbit1.txt",ios::in);
	finr1.open("random0.txt",ios::in);
	finr2.open("random1.txt",ios::in);
	fin1.open("w0.txt",ios::in);
	fin2.open("w1.txt",ios::in);
	fin3.open("z0.txt",ios::in);
	fin4.open("z1.txt",ios::in);
	fin5.open("multiply0.txt",ios::in);
	fin6.open("multiply1.txt",ios::in);
	for(int j=0;j<40;j++)
	{
	string data1,data2;
	int32_t str1[3],str2[3];
	for(int i=0;i<23;i++)
	{
		if(finb1.eof())
		{
			finb1.clear();
			finb1.seekg(0,ios::beg);
		}
		if(finb2.eof())
		{
			finb2.clear();
			finb2.seekg(0,ios::beg);
		}
		getline(finb1,data1);
		getline(finb2,data2);
		stringstream is1(data1);
		stringstream is2(data2);
		is1>>str1[0]>>str1[1]>>str1[2];
		is2>>str2[0]>>str2[1]>>str2[2];
		blow1[i].setSecShare(1,str1[0],str1[1],str1[2]);
		blow2[i].setSecShare(2,str2[0],str2[1],str2[2]);
	}
	int32_t bbb[23];
	int32_t nnn=0;
	int32_t temp;
	for(int i=0;i<23;i++)
	{
		bbb[i]=module((int64_t)blow1[i].share+blow2[i].share);
		temp=int64_t(pow(2.0,i));
 		nnn=nnn+(bbb[i]*temp);
	}
	if(nnn>=Q)
	{
		cout<<"wrong bits chosen "<<endl;
		continue;
	}
	SecShare bhigh1[23],bhigh2[23];
	SecShare a1,a2;
	if(finr1.eof())
	{
		finr1.clear();
		finr1.seekg(0,ios::beg);
	}
	if(finr2.eof())
	{
		finr2.clear();
		finr2.seekg(0,ios::beg);
	}
	getline(finr1,data1);
	getline(finr2,data2);
	stringstream is1(data1);
	stringstream is2(data2);
	is1>>str1[0]>>str1[1];
	is2>>str2[0]>>str2[1];
	a1.setSecShare(1,str1[0],str1[1],0);
	a2.setSecShare(2,str2[0],str2[1],0);
	int32_t c1=194332,c2=3744444;
	int32_t cc=module((int64_t)a1.share+a2.share);

	if(c1<cc && cc<c2)
	{
		cout<<"cc is "<<cc<<' '<<1<<endl;
	}
	else
		cout<<"cc is "<<cc<<' '<<0<<endl;
	intervalt1(a1,blow1,bhigh1,finb1);
	intervalt1(a2,blow2,bhigh2,finb2);
	int32_t c=module((int64_t)a1.share+a2.share);
	
	//cout<<"c is "<<c<<endl;
	
	
	int32_t lowbits[23],highbits[23];
	SecShare aalow1[23],bblow1[23],cclow1[23],aahigh1[23],bbhigh1[23],cchigh1[23];
	SecShare aalow2[23],bblow2[23],cclow2[23],aahigh2[23],bbhigh2[23],cchigh2[23];
	SecShare epsilonsharelow1[23],deltasharelow1[23],epsilonsharehigh1[23],deltasharehigh1[23];
	SecShare epsilonsharelow2[23],deltasharelow2[23],epsilonsharehigh2[23],deltasharehigh2[23];
	
	
	intervalt2(blow1,bhigh1,c,c1,c2,lowbits,highbits,aalow1,bblow1,cclow1,aahigh1,bbhigh1,cchigh1,epsilonsharelow1,
		deltasharelow1,epsilonsharehigh1,deltasharehigh1,fin1,fin5);

	intervalt2(blow2,bhigh2,c,c1,c2,lowbits,highbits,aalow2,bblow2,cclow2,aahigh2,bbhigh2,cchigh2,epsilonsharelow2,
		deltasharelow2,epsilonsharehigh2,deltasharehigh2,fin2,fin6);
	int32_t epsilonlow[23],epsilonhigh[23],deltalow[23],deltahigh[23];
	for(int i=0;i<23;i++)
	{
		epsilonlow[i]=module((int64_t)epsilonsharelow1[i].share+epsilonsharelow2[i].share);
		epsilonhigh[i]=module((int64_t)epsilonsharehigh1[i].share+epsilonsharehigh2[i].share);
		deltalow[i]=module((int64_t)deltasharelow1[i].share+deltasharelow2[i].share);
		deltahigh[i]=module((int64_t)deltasharehigh1[i].share+deltasharehigh2[i].share);
	}
	intervalt3(aalow1,bblow1,cclow1,aahigh1,bbhigh1,cchigh1,epsilonlow,deltalow,epsilonhigh,deltahigh);
	intervalt3(aalow2,bblow2,cclow2,aahigh2,bbhigh2,cchigh2,epsilonlow,deltalow,epsilonhigh,deltahigh);
	int32_t mlow[23],mhigh[23];
	for(int i=0;i<23;i++)
	{
		mlow[i]=module((int64_t)aalow1[i].share+aalow2[i].share);
		mhigh[i]=module((int64_t)aahigh1[i].share+aahigh2[i].share);

	}
	SecShare slow1,shigh1,bitlow1,bithigh1,slow2,shigh2,bitlow2,bithigh2;
	intervalt4(lowbits,highbits,slow1,shigh1,bitlow1,bithigh1,blow1,bhigh1,mlow,mhigh,fin3,finb1);
	intervalt4(lowbits,highbits,slow2,shigh2,bitlow2,bithigh2,blow2,bhigh2,mlow,mhigh,fin4,finb2);
	int32_t slow,shigh;
	slow=module((int64_t)slow1.share+slow2.share);
	shigh=module((int64_t)shigh1.share+shigh2.share);
	SecShare secsharea1,secshareb1,secsharec1,secsharea2,secshareb2,secsharec2;
	SecShare epsilonshare1,epsilonshare2,deltashare1,deltashare2;
	intervalt5(slow,shigh,bitlow1,bithigh1,secsharea1,secshareb1,secsharec1,epsilonshare1,deltashare1,fin5);
	intervalt5(slow,shigh,bitlow2,bithigh2,secsharea2,secshareb2,secsharec2,epsilonshare2,deltashare2,fin6);
	//cout<<"bitlow is "<<bitlow1.share+bitlow2.share<<endl;
	//cout<<"bithigh is "<<bithigh1.share+bithigh2.share<<endl;
	int32_t epsilon,delta;
	epsilon=module((int64_t)epsilonshare1.share+epsilonshare2.share);
	delta=module((int64_t)deltashare1.share+deltashare2.share);
	intervalt6(c,c1,c2,secsharea1,secshareb1,secsharec1,epsilon,delta);
	intervalt6(c,c1,c2,secsharea2,secshareb2,secsharec2,epsilon,delta);
	cout<<module((int64_t)secsharea1.share+secsharea2.share)<<endl;	
}
	finb1.close();
	finb2.close();
	finr1.close();
	finr2.close();
	fin1.close();
	fin2.close();
	fin5.close();
	fin6.close();
	fin3.close();
	fin4.close();
	
/***********************
 * test BitLTC1
 * *********************/
/*	int32_t a=Q;
	ifstream finb1,finb2;
	ifstream fin1,fin2,fin3,fin4,fin5,fin6;
	ifstream finbb1,finbb2;
	finb1.open("randbit0.txt",ios::in);
	finb2.open("randbit1.txt",ios::in);
	fin1.open("w0.txt",ios::in);
	fin2.open("w1.txt",ios::in);
	fin3.open("z0.txt",ios::in);
	fin4.open("z1.txt",ios::in);
	fin5.open("multiply0.txt",ios::in);
	fin6.open("multiply1.txt",ios::in);
	//finbb1.open("randbit0.txt",ios::in);
//	finbb2.open("randbit1.txt",ios::in);
	
	for(int j=0;j<20;j++)
	{
		cout<<endl;
		cout<<j<<": "<<endl;
	

	SecShare b1[23],b2[23];
	string data1,data2;
	int32_t str1[3],str2[3];
	int32_t abits[23];
	for (int i=0;i<23;i++)
	{
		if(finb1.eof())
		{
			finb1.clear();
			finb1.seekg(0,ios::beg);
		}
		if(finb2.eof())
		{
			finb2.clear();
			finb2.seekg(0,ios::beg);
		}
		getline(finb1,data1);
		getline(finb2,data2);
		stringstream is1(data1);
		stringstream is2(data2);
		is1>>str1[0]>>str1[1]>>str1[2];
		is2>>str2[0]>>str2[1]>>str2[2];
		b1[i].setSecShare(1,str1[0],str1[1],str1[2]);
		b2[i].setSecShare(2,str2[0],str2[1],str2[2]);
	}
	int32_t bbb[23];
	int32_t nnn=0;
	for(int i=0;i<23;i++)
	{
		bbb[i]=module((int64_t)b1[i].share+b2[i].share);
	//	cout<<bbb[i]<<'\t';
		int32_t temp=int32_t(pow(2.0,i));
 		nnn=nnn+(bbb[i]*temp);

 	//	cout<<"b i is "<<i<<'\t'<<b1[i].share<<'\t'<<b2[i].share<<'\t';
	}
	//cout<<endl;

	if(nnn<a)
		{cout<<"< "<<nnn<<endl;
		cout<<0<<endl;}
	else
		{
			cout<<"> "<<nnn<<endl;cout<<1<<endl;}

	
	SecShare aa1[23],aa2[23],bb1[23],bb2[23],cc1[23],cc2[23];
	SecShare epsilonshare1[23],epsilonshare2[23],deltashare1[23],deltashare2[23];


	Bitltc1(a,abits,b1,aa1,bb1,cc1,epsilonshare1,deltashare1,fin1,fin5);
	Bitltc1(a,abits,b2,aa2,bb2,cc2,epsilonshare2,deltashare2,fin2,fin6);
/*	for(int i=0;i<23;i++)
	{
		cout<<abits[i]<<'\t';
	}
	cout<<endl;*/

	/*int32_t epsilon[23],delta[23];
	for(int i=0;i<23;i++)
	{
		epsilon[i]=module((int64_t)epsilonshare1[i].share+epsilonshare2[i].share);
		delta[i]=module((int64_t)deltashare1[i].share+deltashare2[i].share);
		//int64_t temp=b1[i].share+b2[i].share;
		//module(temp);
		//cout<<temp<<'\t';
	}
	//cout<<endl;
	Bitltc2(aa1,bb1,cc1,epsilon,delta);
	Bitltc2(aa2,bb2,cc2,epsilon,delta);
	int32_t m[23];
	for(int i=0;i<23;i++)
	{
		m[i]=module((int64_t)aa1[i].share+aa2[i].share);

		
	}
	
	SecShare s1,bit1,s2,bit2;

	
	Bitltc3(abits,s1,bit1,b1,m,fin3,finb1);
	Bitltc3(abits,s2,bit2,b2,m,fin4,finb2);
	
	int32_t s=module((int64_t)s1.share+s2.share);

//	cout<<s<<endl;
	//s=s%2;
	//cout<<s1.share<<'\t'<<s2.share<<'\t'<<s<<endl;
	Bitltc4(s,bit1);
	Bitltc4(s,bit2);
	int32_t result=module((int64_t)bit1.share+bit2.share);
	//cout<<bit1.share<<'\t'<<bit2.share<<endl;	
	cout<<bit1.share<<'\t'<<bit2.share<<'\t'<<result<<endl;
	}
finb1.close();
	finb2.close();
	
		fin1.close();
	fin2.close();
	fin5.close();
	fin6.close();
	fin3.close();
	fin4.close();*/
	//finbb1.close();
	//finbb2.close();


	/*********************************
	 * test premult
	 ********************************/
/*	ifstream finr1,finr2;
	ifstream fin1,fin2,fin3,fin4,fin5,fin6;
	//ifstream finbb1,finbb2;
	finr1.open("random0.txt",ios::in);
	finr2.open("random1.txt",ios::in);
	fin1.open("w0.txt",ios::in);
	fin2.open("w1.txt",ios::in);
	fin3.open("z0.txt",ios::in);
	fin4.open("z1.txt",ios::in);
	fin5.open("multiply0.txt",ios::in);
	fin6.open("multiply1.txt",ios::in);
	string data1,data2;
	int32_t str1[23],str2[23];
	SecShare a1[23],a2[23];
	SecShare aa1[23],bb1[23],cc1[23],epsilonshare1[23],
	deltashare1[23],aa2[23],bb2[23],cc2[23],epsilonshare2[23],
	deltashare2[23],p1[23],p2[23];
	int32_t epsilon[23],delta[23],m[23],a[23];
	int32_t prod;
	for(int j=0;j<40;j++)
	{
	for(int i=0;i<23;i++)
	{
		if(finr1.eof())
		{
			finr1.clear();
			finr1.seekg(0,ios::beg);
		}
		if(finr2.eof())
		{
			finr2.clear();
			finr2.seekg(0,ios::beg);
		}
		
		getline(finr1,data1);
		getline(finr2,data2);
		stringstream is1(data1);
		stringstream is2(data2);
		is1>>str1[0]>>str1[1];
		is2>>str2[0]>>str2[1];
		a1[i].setSecShare(1,str1[0],str1[1],0);
		a2[i].setSecShare(2,str2[0],str2[1],0);
	}

	
	premult1(a1,aa1,bb1,cc1,epsilonshare1,deltashare1,fin1,fin5);
	premult1(a2,aa2,bb2,cc2,epsilonshare2,deltashare2,fin2,fin6);
	for(int i=0;i<23;i++)
	{
		epsilon[i]=module((int64_t)epsilonshare1[i].share+epsilonshare2[i].share);
		delta[i]=module((int64_t)deltashare1[i].share+deltashare2[i].share);

	}
	premult2(aa1,bb1,cc1,epsilon,delta);
	premult2(aa2,bb2,cc2,epsilon,delta);
	for(int i=0;i<23;i++)
	{
		m[i]=module((int64_t)aa1[i].share+aa2[i].share);
	}
	premult3(a1,p1,m,fin3);
	premult3(a2,p2,m,fin4);*/
	
	/**********************
	 * output result
	 ************************/
	/*int32_t p[23];
	prod=1;



	for(int i=0;i<23;i++)
	{
		a[i]=module((int64_t)a1[i].share+a2[i].share);
		prod=module((int64_t)prod*a[i]);
		p[i]=module((int64_t)p1[i].share+p2[i].share);
		cout<<i<<' '<<prod<<' '<<p[i]<<endl;
	}

	cout<<endl;
	cout<<endl;
	}
	finr1.close();
	finr2.close();
	fin1.close();
	fin2.close();
	fin5.close();
	fin6.close();
	fin3.close();
	fin4.close();*/
	
	return 0;
}