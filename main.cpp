#include "Individual.h"

#include <iostream>
#include <string.h>

static int s_rand = (unsigned int) time(NULL);

void generate_Network(){
	int pop=0;
	while(pop <= pop_Size){
		Individual ancestor;
		ancestor.mutation();
		ancestor.development();
		bool steady = ancestor.check_Steady();
		if(steady == true){
			bool fit = ancestor.check_Fitness();
			if(fit == true){
				//save the individual's network into file
				/**/
				cout<<"has one ancestor"<<endl;
				pop++;
			}else{
				cout<<"fail to have one ancestor"<<endl;
			
			}
		}
	}

	
}

Individual generate_parents(){

		Individual ancestor;
		ancestor.mutation();
		ancestor.development();
		bool steady = ancestor.check_Steady();
		if(steady == true){
			bool fit = ancestor.check_Fitness();
			if(fit == true){
				//save the individual into stable network
				/**/
				cout<<"has one ancestor"<<endl;
				return ancestor;
			}else{
				cout<<"fail to have one ancestor"<<endl;
				generate_parents();
			}
		}else{
			cout<<"fail to have one ancestor"<<endl;
			generate_parents();
		}

}

Individual recombination(Individual father,Individual mother){
	srand(s_rand);
	Individual child;
	
	int fi=0,mi=0,ci=0;
		
	for( int ci = 0; ci < gen_Num; ci++){
		double random = (double)( rand() % 10 )/ 10 ;
		if ( 0.5 < random)
		{
			memcpy(child.W[ci],father.W[fi],sizeof(child.W[ci]));
			fi++;
		}else{
			memcpy(child.W[ci],mother.W[mi],sizeof(child.W[ci]));
			mi++;
		}
		cout<<"random:"<<random<<endl;
		for( int j=0; j < gen_Num; j++ ){
			cout<<"child.W[ci][j] is :"<<child.W[ci][j]<<endl;
		}
		s_rand = rand();
	}
	 
	cout<<"sizeof(child.W[ci]) is "<<sizeof(child.W[ci])<<endl;
	return child;
}

int main() {

	//generate first generation
	Individual father = generate_parents();
	cout<<"above is father"<<endl;
	Individual mother = generate_parents();
	cout<<"above is mother"<<endl;

	//generate offspring
	Individual ind = recombination(father,mother);

	//individual develop 
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
