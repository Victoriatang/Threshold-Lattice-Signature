#include <iostream>
#include <fstream>
#include "sign.h"
#include <time.h>
#include <vector>
using namespace std;

static __inline__ unsigned long long GetCycleCount(void)
{
	unsigned hi,lo;
	__asm__ volatile("rdtsc":"=a"(lo),"=d"(hi));
	return ((unsigned long long)lo)|(((unsigned long long)hi)<<32);
}
int main()
{
	clock_t start,end;
	clock_t start1,end1;
	start=clock();
	unsigned long long t1,t2;
	t1=(unsigned long)GetCycleCount();
	ifstream finbit1,finbit2,finbitlessq1,finbitlessq2;
	ifstream fin1,fin2,fin3,fin4,fin5,fin6;
	fin1.open("txtFile/w0.txt",ios::in);
	fin2.open("txtFile/w1.txt",ios::in);
	fin3.open("txtFile/z0.txt",ios::in);
	fin4.open("txtFile/z1.txt",ios::in);
	fin5.open("txtFile/multiply0.txt",ios::in);
	fin6.open("txtFile/multiply1.txt",ios::in);
	finbit1.open("txtFile/randbit0.txt",ios::in);
	finbit2.open("txtFile/randbit1.txt",ios::in);
	finbitlessq1.open("txtFile/randbitlessq0.txt",ios::in);
	finbitlessq2.open("txtFile/randbitlessq1.txt",ios::in);
	for(int k=0;k<50;k++)
	{
	cout<<"k is"<<'\t'<<k<<endl;
	int times=0;
	bool flag=true;
	while(times==0||(!flag && times<5))
	{
	flag=true;
	times++;
	cout<<times<<endl;
	sharetempsec Y1;
	sharetempsec Y2;
	signmessage1 msg11,msg12;
	polyveck w;
	ifstream finA;
	finA.open("txtFile/pk_A.txt",ios::in);
	sign1(finA,finbit1,&Y1,1,&msg11);
	finA.close();
	ifstream finAp;
	finAp.open("txtFile/pk_A.txt",ios::in);
	sign1(finAp,finbit2,&Y2,2,&msg12);
	finAp.close();
	polyveck_openshare(&w,&msg11.wshare,&msg12.wshare);
	unsigned int mlen=10;
	uint8_t m[10]={1,2,3,4,5,6,7,8,9,10};
	signshare zshare1,zshare2;
	signshare zzshare1,zzshare2;
	bitshares_mat bitsmat1,bitsmat2;
	poly chanllenge;
	ifstream finsk1,finsk2;	
	finsk1.open("txtFile/sk0.txt",ios::in);
	finsk2.open("txtFile/sk1.txt",ios::in);
	sign2p(m,mlen,&Y1,finsk1,1,&w,&zshare1,&bitsmat1,
	finbitlessq1,&chanllenge,&zzshare1);
	sign2p(m,mlen,&Y2,finsk2,2,&w,&zshare2,&bitsmat2,
	finbitlessq2,&chanllenge,&zzshare2);
	finsk1.close();
	finsk2.close();
	polyvecl zl;
	polyveck zk;
	polyvecl_openshare(&zl,&zshare1.zlshare,&zshare2.zlshare);
	polyveck_openshare(&zk,&zshare1.zkshare,&zshare2.zkshare);
	vector<int32_t> ccompare;
	vector<vector<int>> position;
	start1=clock();
	for(int i=0;i<L+K;i++)
	{
		for(int j=0;j<N;j++)
		{
			int32_t temp;
		
			if(i<L)
			{
				temp=zl.vec[i].coeffs[j];
				
			}
			else
			{
				temp=zk.vec[i-L].coeffs[j];
			}
			if(temp>=boundhigher)
			{
					//cout<<"direct reject!!!!!!!!!!!!!!!!!"<<endl;
					//cout<<k<<'\t'<<"Reject!!!!!!"<<endl;
					flag=false;
					i=L+K;
					j=N;
			}
			else if(temp<boundhigh)
			{
				continue;
			}
			else{
				
				ccompare.push_back(temp-boundhigh);
				
				position.push_back({i,j});
			
			}
		}
		
	}
	if(flag==false)
	{
		continue;
	}
	int size=ccompare.size();
	
	cout<<"size is:"<<size<<endl;
	SecShare aa1[size][comp_bitsNum],bb1[size][comp_bitsNum],cc1[size][comp_bitsNum],
	epsilonshare1[size][comp_bitsNum],deltashare1[size][comp_bitsNum];
	SecShare aa2[size][comp_bitsNum],bb2[size][comp_bitsNum],cc2[size][comp_bitsNum],
	epsilonshare2[size][comp_bitsNum],deltashare2[size][comp_bitsNum];
	
	
	for(int i=0;i<size;i++)
	{
		int poi,poj;
		poi=position[i][0];
		poj=position[i][1];
		Bitltc1(ccompare[i],bitsmat1.sharemat[poi][poj].bit,aa1[i],bb1[i],cc1[i],
		epsilonshare1[i],deltashare1[i],fin1,fin5);
		Bitltc1(ccompare[i],bitsmat2.sharemat[poi][poj].bit,aa2[i],bb2[i],cc2[i],
		epsilonshare2[i],deltashare2[i],fin2,fin6);

	} 
	for(int i=0;i<size;i++)
	{
		int32_t epsilon[comp_bitsNum],delta[comp_bitsNum];
		for(int j=0;j<comp_bitsNum;j++)
		{
			epsilon[j]=freeze(epsilonshare1[i][j].share+epsilonshare2[i][j].share);
			delta[j]=freeze(deltashare1[i][j].share+deltashare2[i][j].share);
		}
		Bitltc2(aa1[i],bb1[i],cc1[i],epsilon,delta);
		Bitltc2(aa2[i],bb2[i],cc2[i],epsilon,delta);		
	}
	for(int i=0;i<size;i++)
	{
		int32_t mm[comp_bitsNum];
		for(int j=0;j<comp_bitsNum;j++)
		{
			
			mm[j]=freeze(aa1[i][j].share+aa2[i][j].share);
		}
		int poi,poj;
		poi=position[i][0];
		poj=position[i][1];
		Bitltc3(ccompare[i],bb1[i][0],cc1[i][0],bitsmat1.sharemat[poi][poj].bit,
		mm,fin3,finbit1);
		Bitltc3(ccompare[i],bb2[i][0],cc2[i][0],bitsmat2.sharemat[poi][poj].bit,
		mm,fin4,finbit2);
	}
	//the result is bb1[i][0],bb2[i][0]
	SecShare csum1,csum2;
	csum1.setSecShare(1,0,0,0);
	csum2.setSecShare(2,0,0,0);
	for(int i=0;i<size;i++)
	{
		int32_t s;
		s=freeze(bb1[i][0].share+bb2[i][0].share);
		Bitltc4(s,cc1[i][0]); //the result cc1[i][0],cc2[i][0]
		Secadd(csum1,cc1[i][0]);
		Bitltc4(s, cc2[i][0]);
		Secadd(csum2,cc2[i][0]);
	}
	intervalt1p(csum1,aa1[0],finbitlessq1);
	intervalt1p(csum2,aa2[0],finbitlessq2);
	int32_t csum=freeze(csum1.share+csum2.share);
	if (csum>(1<<comp_bitsNum)+size-1)
	{
		cout<<"1Reject!!!!!!!!!!!!"<<endl;
		flag=false;
	}
	if (csum>=size && csum<=(1<<comp_bitsNum)+size-1)
	{
		Bitltc1(csum-size,aa1[0],aa1[1],bb1[1],cc1[1],epsilonshare1[1],
		deltashare1[1],fin1,fin5);
		Bitltc1(csum-size,aa2[0],aa2[1],bb2[1],cc2[1],epsilonshare2[1],
		deltashare2[1],fin2,fin6);
		int32_t epsilon[comp_bitsNum],delta[comp_bitsNum];
		for(int j=0;j<comp_bitsNum;j++)
		{
			epsilon[j]=freeze(epsilonshare1[1][j].share+epsilonshare2[1][j].share);
			delta[j]=freeze(deltashare1[1][j].share+deltashare2[1][j].share);
		}
		Bitltc2(aa1[1],bb1[1],cc1[1],epsilon,delta);
		Bitltc2(aa2[1],bb2[1],cc2[1],epsilon,delta);
		int32_t mm[comp_bitsNum];
		for(int j=0;j<comp_bitsNum;j++)
		{
			
			mm[j]=freeze(aa1[1][j].share+aa2[1][j].share);
		}
		Bitltc3(csum-size,bb1[1][0],cc1[1][0],aa1[0],
		mm,fin3,finbit1);
		Bitltc3(csum-size,bb2[1][0],cc2[1][0],aa2[0],
		mm,fin4,finbit2);	
		int32_t s;
		s=freeze(bb1[1][0].share+bb2[1][0].share);
		Bitltc4(s,cc1[1][0]); //the result cc1[i][0],cc2[i][0]
		Bitltc4(s,cc2[1][0]); //the result cc1[i][0],cc2[i][0]
		int32_t result=freeze(cc1[1][0].share+cc2[1][0].share);
		if(result==1)
		{
			cout<<"Reject!!!!!!!!!!!!"<<endl;
			flag=false;
		}
	}
	if(flag==false)
		continue;
	
	polyvecl_openshare(&zl,&zzshare1.zlshare,&zzshare2.zlshare);
	polyveck_openshare(&zk,&zzshare1.zkshare,&zzshare2.zkshare);
	end1=clock();
	}
	}
	fin1.close();
	fin2.close();
	fin3.close();
	fin4.close();
	fin5.close();
	fin6.close();
//	finA.close();
	finbit1.close();
	finbit2.close();
	finbitlessq1.close();
	finbitlessq2.close();
	end=clock();
	t2=(unsigned long)GetCycleCount();
	cout<<"comparison time="<<double(end1-start1)/CLOCKS_PER_SEC<<endl;
	cout<<"time="<<double(end-start)/CLOCKS_PER_SEC<<endl;
	cout<<t2-t1<<endl;
	return 0;
}

