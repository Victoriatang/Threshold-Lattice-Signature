#include "config.h"
int32_t module(int64_t a)
{
  /*int64_t t;
  int32_t res;

  t = (a + (1 << 22)) >> 23;
  res = (int32_t)a - t*Q;
  res += (res >> 31) & Q;
  return res;*/
 a=a%Q;
  if(a<0)
    a=a+Q;
  return (int32_t)a;
}
void SecShare::setSecShare(int i,int32_t x,int32_t y,int32_t z)
{
	index=i;
	share=x;
	MACshare=y;
	delta=z;

}
void Secadd(SecShare &a,SecShare b)
{
  int32_t x,y,z;
  if(a.index!=b.index){
  	cout<<"Two parties' shares cannot be added!"<<endl;
  	return;
  }
  
  x=module((int64_t)a.share+b.share);
  
  y=module((int64_t)a.MACshare+b.MACshare);

  z=module((int64_t)a.delta+b.delta);

  a.setSecShare(a.index,x,y,z);
}
void Secaddcon(SecShare &a,int32_t e)
{
  int32_t x,z;
  if(a.index==1){
    x=module((int64_t)a.share+e);
    z=module((int64_t)a.delta-e);
  	a.setSecShare(a.index,x,a.MACshare,z);
  }
  else{
  
    z=module((int64_t)a.delta-e);
  	a.setSecShare(a.index,a.share,a.MACshare,z);
  }

}
void Secmulticon(SecShare &a, int32_t e)
{
  int32_t x,y,z;
  x=module((int64_t)e*a.share);

  y=module((int64_t)e*a.MACshare);

  z=module((int64_t)e*a.delta);
  a.setSecShare(a.index,x,y,z);
}
void multiply1(SecShare x,SecShare y,SecShare &a,SecShare &b,SecShare &c,SecShare &epsilonshare,SecShare &deltashare,ifstream &fin)
{
  int32_t zero=0;
  string data;
  stringstream is;
  int32_t str[6];
  if(x.index!=y.index)
  {
    cout<<"Two parties' shares cannot be multiplied!"<<endl;
    return;
  }
  if(fin.eof())
  {
    fin.clear();
    fin.seekg(0,ios::beg);
  }
  getline(fin,data);
  is.clear();
  is.str("");
  is.str(data);
  is>>str[0]>>str[1]>>str[2]>>str[3]>>str[4]>>str[5];
  a.setSecShare(x.index,str[0],str[1],zero);
  b.setSecShare(x.index,str[2],str[3],zero);
  c.setSecShare(x.index,str[4],str[5],zero);
 //cout<<x.share-a.share<<' '<<module((int64_t)x.share-a.share)<<endl;
 // cout<<y.share-b.share<<' '<<module((int64_t)y.share-b.share)<<endl;
  epsilonshare.setSecShare(a.index,a.share,a.MACshare,a.delta);
  
  Secmulticon(epsilonshare,-1);
  Secadd(epsilonshare,x);//x-a
//  cout<<epsilonshare.share<<endl;
  deltashare.setSecShare(b.index,b.share,b.MACshare,b.delta);
  
  Secmulticon(deltashare,-1);
  Secadd(deltashare,y);//y-b
 // cout<<deltashare.share<<endl;

}


void multiply2(SecShare &a,SecShare &b,SecShare &c,int32_t epsilon,int32_t delta)
{
  //cout<<b.delta<<endl;
  Secmulticon(b,epsilon); //b=b*epsilon
  //cout<<"epsiolon is "<<epsilon<<endl;
  //cout<<"b's delta is "<<b.delta<<endl;
  Secmulticon(a,delta); //a=a*delta
  //cout<<"delta is "<<delta<<endl;
  //cout<<"a's delta is "<<a.delta<<endl;
  Secadd(a,b);//a=a+b
  Secadd(a,c);//a=a+c
  Secaddcon(a,module((int64_t)epsilon*delta));//a=a+epsilon*delta
  //cout<<"a's delta is "<<a.delta<<endl;
}