#include "premul.h"

void premult1(SecShare a[comp_bitsNum],SecShare aa[comp_bitsNum],SecShare bb[comp_bitsNum],SecShare cc[comp_bitsNum],
SecShare epsilonshare[comp_bitsNum],SecShare deltashare[comp_bitsNum],ifstream &fin,ifstream &fin1)
{

	SecShare w[comp_bitsNum];
	string data;
	int32_t str[3];	
	stringstream is;
	for (int i=0;i<comp_bitsNum;i++)
	{
		if(fin.eof())
		{
			//cout<<"Read w.txt Done!"<<endl;
			fin.clear();
			fin.seekg(0,ios::beg);
		}
		getline(fin,data);
		is.clear();
		is.str("");
		is.str(data);	
		is>>str[0]>>str[1]>>str[2];		
		w[i].setSecShare(a[0].index,str[0],str[1],str[2]);	
		multiply1(a[i],w[i],aa[i],bb[i],cc[i],epsilonshare[i],deltashare[i],fin1);
	}
}
void premult2(SecShare aa[comp_bitsNum],SecShare bb[comp_bitsNum],SecShare cc[comp_bitsNum],int32_t epsilon[comp_bitsNum],int32_t delta[comp_bitsNum])
{
	for (int i = 0; i < comp_bitsNum; i++)
	{
		multiply2(aa[i],bb[i],cc[i],epsilon[i],delta[i]);//the result is aa[i]
	}
}
void premult3(SecShare a[comp_bitsNum],SecShare p[comp_bitsNum],int32_t m[comp_bitsNum],ifstream &fin)
{
	string data;
	int32_t str[3];
	int32_t prod=1;
	stringstream is;
	for(int i=0;i<comp_bitsNum;i++)
	{
		
		if(fin.eof())
		{
		//	cout<<"Read z.txt Done!"<<endl;
			fin.clear();
			fin.seekg(0,ios::beg);
		}
		prod=module((int64_t)prod*m[i]);

		getline(fin,data);
	//	cout<<i<<' '<<data<<endl;
		is.clear();
		is.str("");
		is.str(data);
		is>>str[0]>>str[1]>>str[2];
		
		p[i].setSecShare(a[0].index,str[0],str[1],str[2]);		
		if(i>0)
		{
			Secmulticon(p[i],prod);
		}
		
	}
	p[0].setSecShare(a[0].index,a[0].share,a[0].MACshare,a[0].delta);
}