#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include "config.h"
using namespace std;
#define Q 8380417
int main()
{
	
	ifstream fin1,fin2;
	fin1.open("multiply0.txt",ios::in);
	fin2.open("multiply1.txt",ios::in);
	ifstream finr1,finr2;
	finr1.open("random0.txt",ios::in);
	finr2.open("random1.txt",ios::in);
	string data1,data2;
	getline(finr1,data1);
	getline(finr2,data2);
	stringstream is1(data1);
	stringstream is2(data2);
	int32_t str1[2],str2[2];
	is1>>str1[0]>>str1[1];
	is2>>str2[0]>>str2[1];
	SecShare x1,x2,y1,y2;
	x1.setSecShare(1,str1[0],str1[1],0);
	x2.setSecShare(2,str2[0],str2[1],0);
	getline(finr1,data1);
	getline(finr2,data2);
	stringstream is11(data1);
	stringstream is22(data2);
	is11>>str1[0]>>str1[1];
	is22>>str2[0]>>str2[1];
	y1.setSecShare(1,str1[0],str1[1],0);
	y2.setSecShare(2,str2[0],str2[1],0);
	int32_t x=module((int64_t)x1.share+x2.share);
	int32_t y=module((int64_t)y1.share+y2.share);
	int32_t z=module((int64_t)x*int64_t(y));
	
	cout<<x<<' '<<y<<' '<<z<<endl;
	SecShare a1,b1,c1,epsilonshare1,deltashare1,a2,b2,c2,epsilonshare2,deltashare2;
	multiply1(x1,y1,a1,b1,c1,epsilonshare1,deltashare1,fin1);
	multiply1(x2,y2,a2,b2,c2,epsilonshare2,deltashare2,fin2);
	cout<<"888888"<<endl;
	cout<<module((int64_t)a1.share+a2.share)<<endl;
	cout<<module((int64_t)b1.share+b2.share)<<endl;
	cout<<module((int64_t)c1.share+c2.share)<<endl;
	cout<<"888888"<<endl;
	int32_t epsilon,delta;
	epsilon=module((int64_t)epsilonshare1.share+epsilonshare2.share);
	delta=module((int64_t)deltashare1.share+deltashare2.share);
	cout<<epsilon<<' '<<delta<<endl;
	multiply2(a1,b1,c1,epsilon,delta);
	multiply2(a2,b2,c2,epsilon,delta);
	int32_t result=module((int64_t)a1.share+a2.share);
	cout<<result<<endl;

	

	/*while(!fin.eof())
	{
		getline(fin,data);
		cout<<data<<endl;
	}*/
	finr1.close();
	finr2.close();
	fin1.close();
	fin2.close();
	return 0;
}