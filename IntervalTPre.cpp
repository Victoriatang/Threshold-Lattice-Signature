
#include "config.h"
#include <fstream>
#include <string>
#include <sstream>
int main(){
	int32_t zero=0;
	int timesnum=50;
	SecShare R1[2*comp_bitsNum],R2[2*comp_bitsNum];
	string data1,data2;
	ifstream fin1,fin2;
	fin1.open("txtFile/random0.txt",ios::in);
	fin2.open("txtFile/random1.txt",ios::in);
	ifstream file1,file2;
	file1.open("txtFile/multiply0.txt",ios::in);
	file2.open("txtFile/multiply1.txt",ios::in);
	ofstream fout11,fout12,fout21,fout22;
	fout11.open("txtFile/w0.txt",ios::out);
	fout12.open("txtFile/w1.txt",ios::out);
	fout21.open("txtFile/z0.txt",ios::out);
	fout22.open("txtFile/z1.txt",ios::out);
	int index1=1,index2=2;
	for(int j=0;j<timesnum;j++)
{
	for(int i=0;i<2*comp_bitsNum;i++)
	{	
		if(fin1.eof())
		{
			fin1.clear();
			fin1.seekg(0,ios::beg);
		}
		getline(fin1,data1);
		int32_t str1[2];
		stringstream is1(data1);
		is1>>str1[0]>>str1[1];
		R1[i].setSecShare(index1,str1[0],str1[1],zero);
		if(fin2.eof())
		{
			fin2.clear();
			fin2.seekg(0,ios::beg);
		}
		getline(fin2,data2);		
		//cout<<data2<<endl;
		int32_t str2[2];
		stringstream is2(data2);
		is2>>str2[0]>>str2[1];
		R2[i].setSecShare(index2,str2[0],str2[1],zero);

	}	
	SecShare r1[comp_bitsNum],r2[comp_bitsNum],s1[comp_bitsNum],s2[comp_bitsNum],v1[comp_bitsNum-1],v2[comp_bitsNum-1],w1[comp_bitsNum],w2[comp_bitsNum],z1[comp_bitsNum],z2[comp_bitsNum];
	int32_t r[comp_bitsNum],s[comp_bitsNum],u[comp_bitsNum];

	for(int i=0;i<comp_bitsNum;i++)
	{
		r1[i].setSecShare(R1[i].index,R1[i].share,R1[i].MACshare,R1[i].delta);
		//cout<<r1[i].index<<'\t'<<R1[i].index<<endl;
		s1[i].setSecShare(R1[comp_bitsNum+i].index,R1[comp_bitsNum+i].share,R1[comp_bitsNum+i].MACshare,R1[comp_bitsNum+i].delta);
		r2[i].setSecShare(R2[i].index,R2[i].share,R2[i].MACshare,R2[i].delta);
		s2[i].setSecShare(R2[comp_bitsNum+i].index,R2[comp_bitsNum+i].share,R2[comp_bitsNum+i].MACshare,R2[comp_bitsNum+i].delta);
		r[i]=module((int64_t)r1[i].share+r2[i].share);
		s[i]=module((int64_t)s1[i].share+s2[i].share);
		u[i]=module((int64_t)s[i]*r[i]);
		
	}

	SecShare a1[comp_bitsNum-1],b1[comp_bitsNum-1],c1[comp_bitsNum-1],a2[comp_bitsNum-1],b2[comp_bitsNum-1],c2[comp_bitsNum-1];
	SecShare epsilonshare1,deltashare1,epsilonshare2,deltashare2;
	int32_t epsilon,delta;
	for(int i=0;i<comp_bitsNum-1;i++)
	{
		//	v[i]=s[i]*r[i+1];
		//	module(v[i]);
			//v[i]=s[i]*r[i+1];
			//module(v[i]);
		   // cout<<v[i]<<endl;
			
			

			multiply1(r1[i+1],s1[i],a1[i],b1[i],c1[i],epsilonshare1,deltashare1,file1);
			multiply1(r2[i+1],s2[i],a2[i],b2[i],c2[i],epsilonshare2,deltashare2,file2);
		//	cout<<"r s is "<<r2[i+1].share<<'\t'<<s2[i].share<<endl;
			epsilon=module((int64_t)epsilonshare1.share+epsilonshare2.share);
			delta=module((int64_t)deltashare1.share+deltashare2.share);
			multiply2(a1[i],b1[i],c1[i],epsilon,delta);
			multiply2(a2[i],b2[i],c2[i],epsilon,delta);
			//cout<<"a1,a1 is "<<a1[i].share<<'\t'<<a2[i].share<<endl;
			v1[i].setSecShare(a1[i].index,a1[i].share,a1[i].MACshare,a1[i].delta);
			v2[i].setSecShare(a2[i].index,a2[i].share,a2[i].MACshare,a2[i].delta);
		//	cout<<v1[i].share<<'\t'<<v2[i].share<<endl;
		//	int64_t k1=v1[i].share+v2[i].share;
		//	module(k1);
		  //  cout<<k1<<'\t'<<v[i]<<endl;
	}
	w1[0].setSecShare(r1[0].index,r1[0].share,r1[0].MACshare,r1[0].delta);
	w2[0].setSecShare(r2[0].index,r2[0].share,r2[0].MACshare,r2[0].delta);
//	cout<<"w is "<<endl;
	for(int i=1;i<comp_bitsNum;i++)
	{
			w1[i].setSecShare(v1[i-1].index,v1[i-1].share,v1[i-1].MACshare,v1[i-1].delta);
			w2[i].setSecShare(v2[i-1].index,v2[i-1].share,v2[i-1].MACshare,v2[i-1].delta);
			//cout<<w1[i].share<<'\t'<<w2[i].share<<endl;
			int32_t uinv=1;
			while(uinv<Q)
			{
				int32_t temp=module((int64_t)uinv*u[i-1]);
				if(temp==1)
					break;
				uinv++;
			}
			Secmulticon(w1[i],uinv);
			Secmulticon(w2[i],uinv);
			int32_t rinv=1;
			while(rinv<Q)
			{
				int32_t temp=module((int64_t)rinv*r[i-1]);
				if(temp==1)
					break;
				rinv++;
			}
	//	cout<<"w is "<<w1[i].share<<'\t'<<w2[i].share<<endl;
			int32_t w=module((int64_t)w1[i].share+w2[i].share);
			int32_t k=module((int64_t)r[i]*rinv);
		//	cout<<w<<' '<<k<<endl;
	}
	for(int i=0;i<comp_bitsNum;i++)
	{
		int32_t uinv=1;
		while(uinv<Q)
		{
			int32_t temp=module((int64_t)uinv*u[i]);
			if(temp==1)
				break;
			uinv++;
		}
		z1[i].setSecShare(s1[i].index,s1[i].share,s1[i].MACshare,s1[i].delta);
		z2[i].setSecShare(s2[i].index,s2[i].share,s2[i].MACshare,s2[i].delta);
		Secmulticon(z1[i],uinv);
		Secmulticon(z2[i],uinv);
		int32_t z=module((int64_t)(z1[i].share+z2[i].share)*r[i]);
		//cout<<z<<endl;
		if(j==timesnum-1 && i==comp_bitsNum-1)
		{
		fout11<<w1[i].share<<'\t'<<w1[i].MACshare<<'\t'<<w1[i].delta;
		fout12<<w2[i].share<<'\t'<<w2[i].MACshare<<'\t'<<w2[i].delta;
		fout21<<z1[i].share<<'\t'<<z1[i].MACshare<<'\t'<<z1[i].delta;
		fout22<<z2[i].share<<'\t'<<z2[i].MACshare<<'\t'<<z2[i].delta;
		}
		else{
			fout11<<w1[i].share<<'\t'<<w1[i].MACshare<<'\t'<<w1[i].delta<<endl;
		fout12<<w2[i].share<<'\t'<<w2[i].MACshare<<'\t'<<w2[i].delta<<endl;
		fout21<<z1[i].share<<'\t'<<z1[i].MACshare<<'\t'<<z1[i].delta<<endl;
		fout22<<z2[i].share<<'\t'<<z2[i].MACshare<<'\t'<<z2[i].delta<<endl;
		}
		

	}
}
fin1.close();
	fin2.close();
	file1.close();
	file2.close();
	fout11.close();
		fout12.close();
		fout21.close();
		fout22.close();


}