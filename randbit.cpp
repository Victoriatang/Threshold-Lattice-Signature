#include "randbit.h"


void randbit1(SecShare &r, SecShare &a,SecShare &b,SecShare &c,int64_t &epsilonshare,int64_t &deltashare,int index,ifstream &fin1,ifstream &fin2)
{
	int64_t zero=0;	
	string data;
	getline(fin1,data);
	//cout<<data<<endl;
	int64_t str[2];
	stringstream is(data);
	is>>str[0]>>str[1];
	//lineNum++;
	r.setSecShare(index,str[0],str[1],zero);
	multiply1(r,r,a,b,c,epsilonshare,deltashare,fin2);
}
void randbit2(SecShare &a,SecShare &b,SecShare &c,int64_t epsilon,int64_t delta)
{
	multiply2(a,b,c,epsilon,delta);//the result is a
}
void randbit3(SecShare &r,int64_t u)
{
	int64_t i=1,j=1;
	while(i<Q)
	{
		int64_t v=i*i;
		module(v);
		if(v==u)
			break;
		i++;
	}
	while(j<Q)
	{
		int64_t ij=i*j;
		module(ij);
		if(ij==1)
			break;
		j++;
	}
	Secmulticon(r,j);
	Secaddcon(r,1);
	//cout<<"r's delta is "<<r.delta<<endl;
	Secmulticon(r,inv2);
	//cout<<"r's delta is "<<r.delta<<endl;
}