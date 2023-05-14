#include "BitLTC1.h"
void Bitltc1(int32_t a, SecShare b[comp_bitsNum],SecShare aa[comp_bitsNum],SecShare bb[comp_bitsNum],SecShare cc[comp_bitsNum],
SecShare epsilonshare[comp_bitsNum],SecShare deltashare[comp_bitsNum],ifstream &fin,ifstream &fin1)
{ //the input of the problem is a and b[comp_bitsNum], the output is abits[comp_bitsNum],b[comp_bitsNum]，b[i]=ai+bi-2ai*bi+1(reorder). (d,aa,bb,cc,epsilonshare,deltashare fin,fin1 are used for prmult) 
 int32_t abits[comp_bitsNum];
 for(int i=0;i<comp_bitsNum;i++)
 {
 	abits[i]=a%2; 
 	a=a/2;
 }
SecShare d[comp_bitsNum];
for(int i=0;i<comp_bitsNum;i++)
{
	d[i].setSecShare(b[i].index,b[i].share,b[i].MACshare,b[i].delta); 
}

 SecShare temp;
 for(int i=0;i<comp_bitsNum;i++)
 {
 	temp.setSecShare(d[i].index,d[i].share,d[i].MACshare,d[i].delta);
 	Secmulticon(temp,module((int64_t)-2*abits[i]));// the result is bi*(-2ai)
 	Secaddcon(d[i],abits[i]);//the result is bi+ai
 	Secadd(d[i],temp);// the result is bi*(-2ai)+bi+ai
 	Secaddcon(d[i],1);//the result is bi*(-2ai)+bi+ai+1
 	b[comp_bitsNum-1-i].setSecShare(d[i].index,d[i].share,d[i].MACshare,d[i].delta);
 	
 }
// b0 b1 b2 ..... bcomp_bitsNum-1
// dcomp_bitsNum-1 d21  ..... d0

 premult1(b,aa,bb,cc,epsilonshare,deltashare,fin,fin1);
}

void Bitltc2(SecShare aa[comp_bitsNum],SecShare bb[comp_bitsNum],SecShare cc[comp_bitsNum],int32_t epsilon[comp_bitsNum],int32_t delta[comp_bitsNum])
{ //aa,bb,cc,epsilon,delta  are used for premult
	premult2(aa,bb,cc,epsilon,delta);
}
void Bitltc3(int32_t a,SecShare &s, SecShare &bit,SecShare b[comp_bitsNum],int32_t m[comp_bitsNum],ifstream &fin,ifstream &finb)
{//b,m,fin are used for prmult, the result is p[comp_bitsNum], the output is s,bit  finb is used for reading random bit SecShare bit
	int32_t abits[comp_bitsNum];
	for(int i=0;i<comp_bitsNum;i++)
 	{
 		abits[i]=a%2; 
 		a=a/2;
 	}
	SecShare pp[comp_bitsNum];
	SecShare p[comp_bitsNum];
	stringstream is;
	premult3(b,p,m,fin);// the result is p
	for(int i=0;i<comp_bitsNum;i++)
	{
		pp[i].setSecShare(p[comp_bitsNum-1-i].index,p[comp_bitsNum-1-i].share,p[comp_bitsNum-1-i].MACshare,p[comp_bitsNum-1-i].delta);//reorder
	}
	SecShare temp;
	for(int i=0;i<comp_bitsNum-1;i++)
	{
		
		temp.setSecShare(pp[i+1].index,pp[i+1].share,pp[i+1].MACshare,pp[i+1].delta);
		Secmulticon(temp,-1);//temp=-pp[i+1]
		Secadd(pp[i],temp);//pp[i]=pp[i]-pp[i+1]
		
	}
	Secaddcon(pp[comp_bitsNum-1],-1);//pp[comp_bitsNum-1]=pp[comp_bitsNum-1]-1
	s.setSecShare(pp[0].index,0,0,0);
	for (int i=0;i<comp_bitsNum;i++)
	{
	//	s.setSecShare(p[0].index,p[0].share,p[0].MACshare,p[0].delta);
		Secmulticon(pp[i],1-abits[i]);
		Secadd(s,pp[i]);
		

	}
	
	//cout<<"before： "<<s.share<<endl;
	if(finb.eof())
	{
		finb.clear();
		finb.seekg(0,ios::beg);
	}
	string data;
	getline(finb,data);
	is.clear();
	is.str("");
	is.str(data);
	int32_t str[3];
	is>>str[0]>>str[1]>>str[2];
	bit.setSecShare(b[0].index,str[0],str[1],str[2]);
	//cout<<"bit is "<<bit.share<<endl;
	Secadd(s,bit); //s=s+bit
	//cout<<"after: "<<s.share<<endl;
}
void Bitltc3minus(int32_t a,SecShare &s, SecShare &bit,SecShare b[comp_bitsNum],int32_t m[comp_bitsNum],ifstream &fin,ifstream &finb)
{//b,m,fin are used for prmult, the result is p[comp_bitsNum], the output is s,bit  finb is used for reading random bit SecShare bit
	int32_t abits[comp_bitsNum];
	for(int i=0;i<comp_bitsNum;i++)
 	{
 		abits[i]=a%2; 
 		a=a/2;
 	}
	SecShare pp[comp_bitsNum];
	SecShare p[comp_bitsNum];
	stringstream is;
	int32_t str[3];
	string data;
	premult3(b,p,m,fin);// the result is p
	for(int i=0;i<comp_bitsNum;i++)
	{
		pp[i].setSecShare(p[comp_bitsNum-1-i].index,p[comp_bitsNum-1-i].share,p[comp_bitsNum-1-i].MACshare,p[comp_bitsNum-1-i].delta);//reorder
	}
	SecShare temp;
	for(int i=0;i<comp_bitsNum-1;i++)
	{
		
		temp.setSecShare(pp[i+1].index,pp[i+1].share,pp[i+1].MACshare,pp[i+1].delta);
		Secmulticon(temp,-1);//temp=-pp[i+1]
		Secadd(pp[i],temp);//pp[i]=pp[i]-pp[i+1]
		
	}
	Secaddcon(pp[comp_bitsNum-1],-1);//pp[comp_bitsNum-1]=pp[comp_bitsNum-1]-1
	s.setSecShare(pp[0].index,0,0,0);
	for (int i=0;i<comp_bitsNum;i++)
	{
	//	s.setSecShare(p[0].index,p[0].share,p[0].MACshare,p[0].delta);
		Secmulticon(pp[i],abits[i]);
		Secadd(s,pp[i]);
		

	}
	
	//cout<<"before： "<<s.share<<endl;
	if(finb.eof())
	{
		finb.clear();
		finb.seekg(0,ios::beg);
	}	
	getline(finb,data);
	is.clear();
	is.str("");
	is.str(data);
	is>>str[0]>>str[1]>>str[2];
	bit.setSecShare(b[0].index,str[0],str[1],str[2]);
	//cout<<"bit is "<<bit.share<<endl;
	Secadd(s,bit); //s=s+bit
	//cout<<"after: "<<s.share<<endl;
}
void Bitltc4(int32_t c, SecShare &bit)
{   //c is  the last result, bit is output
	int32_t cbits[comp_bitsNum];

	 for(int i=0;i<comp_bitsNum;i++)
 	{
 		cbits[i]=c%2; 
 		c=c/2;
 	}
 	SecShare temp;
 	temp.setSecShare(bit.index,bit.share,bit.MACshare,bit.delta);//temp=bit
 	Secmulticon(temp,module((int64_t)-2*cbits[0]));//the result is temp=-2*c1*bit
 	Secaddcon(bit,cbits[0]);//the result is bit=bit+c1
 	Secadd(bit,temp);//the resultis bit=bit+c1-2c1*bit

}