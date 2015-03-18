#define gen_Num 4 //number of genes
#define c 0.75 //network connectivity
#define pop_Size 10000 //population size
#define a 100 //activation constant
#define iter_T 10 //iteration times for stable development
#define tau 10 //time interval used for checking stability
#define avg_T 10 //times for caculating divertion from average gene expression pattern
#define stability 0.001
#define fsigma 100


#include <iostream>

using namespace std;

class Individual
{
	public:
		Individual(void);
		~Individual(void);
		//void collect_Stable_GRNs();
		//void collect_Unstable_GRNs();
		
		double normal_Dis(double);
		void init_OriginalS();
		void shuffle(int *, int); //shuffle the order of the index of w collection in order to randomly set mutation
		void mutation();
		void development();
		void cal_avg_S();
		double cal_D(double *, double *);
		bool check_Steady();
		bool check_Fitness();

	private:
		double W[gen_Num][gen_Num];
		double S[iter_T][gen_Num];
		double avg_S[gen_Num];
		double D[avg_T];
		bool Steady;
		bool Survive;
};
