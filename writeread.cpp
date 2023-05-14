#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include "params.h"
#include "config.h"
//#include <string>
//#include <vector>
using namespace std;

int main(){
	int32_t alpha=3993562;
	ofstream fout0;
	ofstream fout1;
	//fout0.open("randbit0.txt",ios::out);
	//fout1.open("randbit1.txt",ios::out);
	//int32_t delta=4190208;
	fout0.open("txtFile/randbitlessq2.txt",ios::out);
	//if(!fout0.is_open())
	//	cout<<"Open file multiply0.txt failure"<<endl;//打开第一个文件
	
	fout1.open("txtFile/randbitlessq3.txt",ios::out);
//	if(!fout1.is_open())s
//		cout<<"Open file multiply1.txt failure"<<endl;//打开第二个文件
	srand((int)time(NULL));
	for(int i=0;i<1000;i++)
	{
	//	int32_t a=rand()%Q;
	//	int32_t bit;
		for(int j=0;j<23;j++)
		{
			//bit=a%2;
			int32_t share0=rand()%Q;
			int32_t MACshare0=rand()%Q;
			int32_t share1=module(Q-share0);
			int32_t MACshare1=module(Q-MACshare0);
			fout0<<share0<<'\t'<<MACshare0<<endl;
			fout1<<share1<<'\t'<<MACshare1<<endl;
		//	a=a/2;
		}

	}
	fout0.close();
	fout1.close();
/*	for(int i=0;i<10000;i++){
		int32_t ashare0=rand()%Q;
		int32_t aMAC0=rand()%Q;
		int32_t bshare0=rand()%Q;
		int32_t bMAC0=rand()%Q;
		int32_t cshare0=rand()%Q;
		int32_t cMAC0=rand()%Q;
		int32_t a=rand()%Q;
		int32_t b=rand()%Q;
		int32_t c=module((int64_t)a*b);
		int32_t ashare1=module((int64_t)a-ashare0);
		int32_t aMAC1=module((int64_t)alpha*a-aMAC0);
		int32_t bshare1=module((int64_t)b-bshare0);
		int32_t bMAC1=module((int64_t)alpha*b-bMAC0);
		int32_t cshare1=module((int64_t)c-cshare0);
		int32_t cMAC1=module((int64_t)alpha*c-cMAC0);
		if(i==9999)
		{
			fout0<<ashare0<<'\t'<<aMAC0<<'\t'<<bshare0<<'\t'<<bMAC0<<'\t'<<cshare0<<'\t'<<cMAC0;
			fout1<<ashare1<<'\t'<<aMAC1<<'\t'<<bshare1<<'\t'<<bMAC1<<'\t'<<cshare1<<'\t'<<cMAC1;
		}
		else{
			fout0<<ashare0<<'\t'<<aMAC0<<'\t'<<bshare0<<'\t'<<bMAC0<<'\t'<<cshare0<<'\t'<<cMAC0<<endl;
			fout1<<ashare1<<'\t'<<aMAC1<<'\t'<<bshare1<<'\t'<<bMAC1<<'\t'<<cshare1<<'\t'<<cMAC1<<endl;
		}
		
		}*/
	/*for(int i=0;i<10000;i++)
	{
		int32_t bshare0=rand()%Q;
		int32_t bMAC0=rand()%Q;
		int32_t b=rand()%2;
		int32_t bshare1=module((int64_t)b-bshare0);
		int32_t bMAC=module((int64_t)alpha*(b+delta));
		int32_t bMAC1=module((int64_t)bMAC-bMAC0);
		if(i==9999)
		{
		fout0<<bshare0<<'\t'<<bMAC0<<'\t'<<delta;
		fout1<<bshare1<<'\t'<<bMAC1<<'\t'<<delta;
		}
		else{
		fout0<<bshare0<<'\t'<<bMAC0<<'\t'<<delta<<endl;
		fout1<<bshare1<<'\t'<<bMAC1<<'\t'<<delta<<endl;
		}

	}*/

	/*for(int j=0;j<10000;j++)
	{
		int32_t rshare0=rand()%Q;
		int32_t rMAC0=rand()%Q;
		int32_t r=rand()%Q;
		int32_t rshare1=module((int64_t)r-rshare0);
		int32_t rMAC1=module((int64_t)alpha*r-rMAC0);
		if(j==9999)
		{
			fout0<<rshare0<<'\t'<<rMAC0;
			fout1<<rshare1<<'\t'<<rMAC1;
		}
		else
		{
			fout0<<rshare0<<'\t'<<rMAC0<<endl;
			fout1<<rshare1<<'\t'<<rMAC1<<endl;
		}
		
	}
	fout0.close();
	fout1.close();*/
	/*for(int i=0;i<100;i++){
		int64_t ashare0=rand()%Q;
		int64_t aMAC0=rand()%Q;
		int64_t bshare0=rand()%Q;
		int64_t bMAC0=rand()%Q;
		int64_t cshare0=rand()%Q;
		int64_t cMAC0=rand()%Q;
		int64_t a=rand()%Q;
		int64_t b=rand()%Q;
		int64_t c=a*b;
		module(c);
		int64_t ashare1=a-ashare0;
		module(ashare1);
		int64_t aMAC1=alpha*a-aMAC0;
		module(aMAC1);
		int64_t bshare1=b-bshare0;
		module(bshare1);
		int64_t bMAC1=alpha*b-bMAC0;
		module(bMAC1);
		int64_t cshare1=c-cshare0;
		module(cshare1);
		int64_t cMAC1=alpha*c-cMAC0;
		module(cMAC1);
		fout0<<ashare0<<'\t'<<aMAC0<<'\t'<<bshare0<<'\t'<<bMAC0<<'\t'<<cshare0<<'\t'<<cMAC0<<endl;
		fout1<<ashare1<<'\t'<<aMAC1<<'\t'<<bshare1<<'\t'<<bMAC1<<'\t'<<cshare1<<'\t'<<cMAC1<<endl;
		int64_t amac=alpha*a;
		module(amac);
		int64_t bmac=alpha*b;
		module(bmac);
		int64_t cmac=alpha*c;
		module(cmac);
		//cout<<a<<'\t'<<amac<<'\t'<<b<<'\t'<<bmac<<'\t'<<c<<'\t'<<cmac<<endl;
		}
	fout0.close();
	fout1.close();

	ofstream outfile0,outfile1;
	outfile0.open("random0.txt",ios::app);
	if(!outfile0.is_open())
		cout<<"Open  file random0.txt failure"<<endl;//打开第一个文件
	outfile1.open("random1.txt",ios::app);
	if(!outfile1.is_open())
		cout<<"Open  file random1.txt failure"<<endl;//打开第二个文件


	
	outfile0.close();
	outfile1.close();*/
		
	
	return 0;
}