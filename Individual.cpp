

#include "Individual.h"


using namespace std;

static int s_rand = (unsigned int) time(NULL);


Individual::Individual(void)
{
	init_W();
	init_OriginalS();
}

Individual::~Individual(void)
{
}

double Individual::normal_Dis(double x){
	return 1.0/sqrt(2*pi)/sigma*exp(-1*(x-miu)*(x-miu)/(2*sigma*sigma));
}

void Individual::init_W(){
	srand(s_rand);
	
	//initial W[i][j]
	for( int i = 0; i < gen_Num; i++){
		for( int j = 0; j < gen_Num; j++){

			double x,y,scope;
			do{
				x = rand() % ( upper_limit - lower_limit + 1 ) + lower_limit;
				y = normal_Dis(x);
				scope = rand() / (RAND_MAX+1) * normal_Dis(miu); 
			}while ( scope > y );
			W[i][j] = x;
		}
	}
	s_rand = rand(); 

}



void Individual::init_OriginalS(){

	srand(s_rand);
	
	for( int i = 0; i < gen_Num; i++){
		if ( 0.5 < (double)( rand() % 10 )/ 10 )
			S[0][i] = 1;
		else
			S[0][i] = -1;
		cout<<"S[0]["<<i<<"] is :"<<S[0][i]<<endl;
	}
	s_rand = rand(); 
}




void Individual::shuffle(int *arr, int size){
	srand(s_rand);
	for (int i = 0; i < size-1 ; i++){
		  int j = i + rand() / (RAND_MAX / (size - i)+1);
          int t = arr[j];
          arr[j] = arr[i];
          arr[i] = t;
	}
	s_rand = rand(); 
}


void Individual::mutation(){
	//tmp used to store random order of the index of w[][]
	int tmp[gen_Num*gen_Num];
	for( int i = 0; i < gen_Num*gen_Num; i++){
		tmp[i]=i;
	}
	shuffle(tmp,(gen_Num*gen_Num));
	/*for( int i = 0; i < gen_Num*gen_Num; i++){
		cout<<"tmp[i]"<<tmp[i]<<endl;
	}*/
	for( int i = 0; i < gen_Num*gen_Num*(1-c); i++){
		double x,y,scope;
			do{
				x = rand() % ( upper_limit - lower_limit + 1 ) + lower_limit;
				y = normal_Dis(x);
				scope = rand() / (RAND_MAX+1) * normal_Dis(miu); 
			}while ( scope > y );
		W[tmp[i]/gen_Num][tmp[i]%gen_Num] = x;
		s_rand = rand();
	}

}

void Individual::development(){

	for(int t = 1; t < iter_T; t++){
		//cout<<"generation "<<t<<" : "<<endl;
		for(int i = 0; i < gen_Num; i++){
			double SUM = 0;
			for (int j = 0; j < gen_Num; j++){
				SUM +=  W[i][j] * S[t-1][j];
			}
			S[t][i] = 2 / (1 + exp( -1*a*SUM)) - 1;
			//cout<<"S["<<t<<"]["<<i<<"] is :"<<S[t][i]<<endl;
		}
	}
}

void Individual::cal_avg_S(){
	
	for(int i = 0; i < gen_Num; i++){
		double SUM = 0;
		for (int t = iter_T - avg_T; t < iter_T; t++){
			SUM += S[t][i];
		}
		avg_S[i] = SUM / avg_T;
		cout<<"avg_S["<<i<<"] is :"<<avg_S[i]<<endl;
	}
}

double Individual::cal_D(double *S1, double *S2){

		double SUM = 0;
		for(int i = 0; i < gen_Num; i++){
			SUM = SUM + pow((double)(S1[i]-S2[i]) , 2);
		}
		SUM = SUM / ( 4 * gen_Num);
		return SUM;
}

bool Individual::check_Steady(){
	cal_avg_S();

	for (int t = iter_T - avg_T; t < iter_T; t++){	
		D[t] = cal_D(S[t],avg_S);
		//cout<<"D["<<t<<"] is :"<<D[t]<<endl;
	}

	double SUM = 0;
	for (int t = iter_T - avg_T; t < iter_T; t++){
		SUM = SUM + D[t];
	}
	
	cout<<"SUM_D is :"<<SUM<<endl;
	if ( SUM <= stability )
	{
		Steady = true;
	}else
		Steady = false;
		

	cout<<"the steady state is :"<<Steady<<endl;
	return Steady;
	
}

bool Individual::check_Fitness(){

	double SUM = cal_D(S[iter_T],avg_S);
	double fitness = exp(-1*SUM/fsigma);
	if ( fitness > (double)( rand() % 10 )/ 10 ){
		//survive
		Survive = true;
	}else
		Survive = false;

	cout<<"the survive is :"<<Survive<<endl;
	return Survive;
}

void Individual::show_W(){
	
	for( int i = 0; i < gen_Num; i++){
		for(int j=0; j < gen_Num; j++){
			cout<<j<<": W["<<i<<"]["<<j<<"]:"<<W[i][j]<<endl;
		}
	}
}	
