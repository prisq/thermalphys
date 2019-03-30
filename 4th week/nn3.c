#include<stdio.h>
#include <stdlib.h>
#include<math.h>

double activation(double u);
double activation_derivative(double u);

int main(){
	double x[4]={0,1,1,0};
	double y[3][1]={{0},{1},{0}};

	double w1[3][4]={{1,2,3,4},
					{3,4,5,6},
					{5,6,7,8}};
	double b1[3][1]={{1},{2},{3}};
	double a1[3][1]={{0},{0},{0}};
	double eo[3][1]={{0},{0},{0}};

	double wo[3][3]={{1,2,3},
					{3,4,5},
					{5,6,7}};
	double bo[3][1]={{1},{2},{3}};
	double ao[3][1]={{0},{0},{0}};
	double eo[3][1]={{0},{0},{0}};


	for(int i=0; i<3; i++){
		for(int j=0; j<4; j++){
			w1[i][j]=(double)rand()/RAND_MAX;
			//printf("%lf\n", w1[i][j]);
		}
	}

	for(int i=0; i<3; i++){
		for(int j=0; j<1; j++){
			b1[i][j]=(double)rand()/RAND_MAX;
		}
	}

	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			wo[i][j]=(double)rand()/RAND_MAX;
		}
	}

	for(int i=0; i<3; i++){
		for(int j=0; j<1; j++){
			bo[i][j]=(double)rand()/RAND_MAX;
		}
	}


	printf("l=1\n");
	for (int i=0; i<4; i++){
		printf("%lf\n",x[i]);
	}

	printf("l=2\n");
	for(int i =0; i<3; i++){
		for(int j=0; j<4; j++){
			a1[i][0]+=w1[i][j]*x[j];
		}
		a1[i][0]+=b1[i][0];
		e1[i][0]=activation_derivative(a1[i][0]);
		a1[i][0]=activation(a1[i][0]);
		printf("%lf\n", a1[i][0]);
	}

	printf("l=3\n");
	for(int i =0; i<3; i++){
		for(int j=0; j<3; j++){
			ao[i][0]+=wo[i][j]*x[j];
		}
		ao[i][0]+=bo[i][0];
		eo[i][0]=activation_derivative(ao[i][0]);
		ao[i][0]=activation(ao[i][0]);
		printf("%lf\n", ao[i][0]);
	}

	printf("delta of l=3\n");
	for(int i =0; i<3; i++){
		//printf("%lf %lf\n", ao[i][0], eo[i][0]);
		//printf("%lf\n", (ao[i][0]-y[i][0]));

		eo[i][0]*=2*(ao[i][0]-y[i][0]);
		printf("%lf\n", eo[i][0]);
	}

	printf("delta of l=2\n");
	for(int i =0; i<3; i++){
		//e1[i][0]*=2*(ao[i][0]-y[i][0]);
		printf("%lf\n", e1[i][0]);
	}


	return 0;
}

double activation(double u){
	return 1.0/(1.0+exp(-u));
}

double activation_derivative(double u){
	return exp(-u)/pow((1.0+exp(-u)),2);
}

