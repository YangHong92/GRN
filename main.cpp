#include "Individual.h"

#include <iostream>
#include <string.h>

double normal_Dis(double x){
	return 1.0/sqrt(2*pi)/sigma*exp(-1*(x-miu)*(x-miu)/(2*sigma*sigma));
}

void generate_Network(){
	srand((unsigned int) time(NULL));

	double N[gen_Num][gen_Num];

	//initial w[i][j]
	for( int i = 0; i < gen_Num; i++){
		for( int j = 0; j < gen_Num; j++){

			double x,y,scope;
			do{
				x = rand() % ( upper_limit - lower_limit + 1 ) + lower_limit;
				y = normal_Dis(x);
				scope = rand() / (RAND_MAX+1) * normal_Dis(miu); 
			}while ( scope > y );
			N[i][j] = x;
		}
	}
	cout<<"before shuffle: "<<endl;
	for( int i = 0; i < gen_Num; i++){
		for(int j=0; j < gen_Num; j++){
			cout<<j<<": N[i][j]:"<<N[i][j]<<endl;
		}
	}

	
}

Individual recombination(){
	Individual c;
	
	//read parents from file
	Individual f;
	Individual m;
	
	int fi=mi=ci=0;
	for( int ci = 0; ci < gen_Num; ci++){
		if ( 0.5 < (double)( rand() % 10 )/ 10 )
		{
			memcpy(c.W[ci],f.W[fi],gen_Num);
			fi++;
		}else{
			memcpy(c.W[ci],m.W[mi],gen_Num);
			mi++;
		}
		for( int j=0; j < gen_Num; j++ ){
			cout<<"c.W[ci][j] is :"<<c.W[ci][j]<<endl;
		}
	}

	return c;
}
int main() {

	//generate first generation
	for(int i=0; i<pop_Size; i++){
		generate_Network();
		
		//save individual into file

	}

	//generate offspring
	Individual ind = combination();

	ind.mutation();
	ind.development();
	bool steady = ind.check_Steady();
	if(steady == true){
		bool fit = ind.check_Fitness();
		if(fit == true){
			//save the individual into stable network

		}
	}else{
		//save the individual into unstable network

	}

	system("pause");
	
	return 0;

}
