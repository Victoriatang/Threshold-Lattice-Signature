#include "polyvec.h"
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	//Generate A
	polyvecl mat[K];
	ofstream fout;
	fout.open("txtFile/pk_A.txt",ios::out);
	polyvec_matrix(mat,fout);
	fout.close();


	//Generate share's of s,e 
	polysharevecl s0,s1;
	polyshareveck e0,e1;
	ofstream fout0,fout1;
	ifstream fin0,fin1;
	fin0.open("txtFile/randbit0.txt",ios::in);
	fin1.open("txtFile/randbit1.txt",ios::in);
	fout0.open("txtFile/sk0.txt",ios::out);
	fout1.open("txtFile/sk1.txt",ios::out);
	polyvecl_sharesecret(&s0,fin0,1,fout0);
	polyveck_sharesecret(&e0,fin0,1,fout0);
	polyvecl_sharesecret(&s1,fin1,2,fout1);
	polyveck_sharesecret(&e1,fin1,2,fout1);
	fin0.close();
	fin1.close();
	fout0.close();
	fout1.close();

    //Refresh shares of s,e
    polyvecl_sharesecret(&s0,fin0,1,fout0);
	polyveck_sharesecret(&e0,fin0,1,fout0);
	polyvecl_sharesecret(&s1,fin1,2,fout1);
	polyveck_sharesecret(&e1,fin1,2,fout1);


	/*polyshareveck t0,t1;
	polyvec_matrix_pointwise_montgomery(&t0,mat,s0);
	polyveck_add(&t0,&t0,&e0);
	polyvec_matrix_pointwise_montgomery(&t1,mat,s1);
	polyveck_add(&t1,&t1,&e1);*/



	

}