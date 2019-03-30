#include<stdio.h>
#include <stdlib.h>
#include<math.h>

double activation(double u);

int main(){
	double x[2]={1,2};

	double w1[3][2]={{1,2},
					{3,4},
					{5,6}};
	double b1[3][1]={{1},{2},{3}};
	double a1[3][1]={{0},{0},{0}};

	double wo[3]={1,2,3};
	double bo=1;
	double ao=0;

	printf("l=1\n");
	for (int i=0; i<2; i++){
		printf("%lf\n",x[i]);
	}

	printf("l=2\n");
	for(int i =0; i<3; i++){
		for(int j=0; j<2; j++){
			a1[i][0]+=w1[i][j]*x[j];
		}
		a1[i][0]+=b1[i][0];
		a1[i][0]=activation(a1[i][0]);
		printf("%lf\n", a1[i][0]);
	}

	printf("l=3\n");
	for(int i=0; i<3; i++){
		ao+=wo[i]*a1[i][0];
	}
	ao+=bo;
	ao=activation(ao);
	printf("%lf\n", ao);

	return 0;
}

double activation(double u){
	return 1.0/(1.0+exp(-u));
}
