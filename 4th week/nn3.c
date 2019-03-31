#include<stdio.h>
#include <stdlib.h>
#include<math.h>

#define xdim 4 //l=1
#define l2no 3
#define ydim 3 //l=3
#define m 1 //m is # of training sets
#define lrate 0.001 //learning rate
#define iter 5 // # of iteration 

double activation(double u);
double activation_derivative(double u);
void randomize(double w1[l2no][xdim], double b1[l2no], double wo[ydim][l2no], double bo[ydim]);
void descent(double w1[l2no][xdim], double b1[l2no], double a1[l2no][m], double e1[l2no][m],
			double wo[ydim][l2no], double bo[ydim], double a0[ydim][m], double e0[ydim][m]);

int main(){

	//1.Input
	double x[xdim][m]={{0},
					{1},
					{1},
					{0}};
	double y[ydim][m]={{0},
					{1},
					{0}};

	double w1[l2no][xdim];
	double b1[l2no];  //bias
	double a1[l2no][m]={0,};  //activation(z)
	double e1[l2no][m]={0,};  //delta
	double p1[l2no][m]={0,};  //activation_derivative(z)

	double wo[ydim][l2no];
	double bo[ydim];
	double ao[ydim][m]={0,};
	double eo[ydim][m]={0,};
	double po[ydim][m]={0,};

	randomize(w1,b1,wo,bo);

	//Iterate until it reachs tolerance 
	for(int epoch=0; epoch<iter; epoch++){
		printf("Epoch : %d\n", epoch);

		//For k-th traing exmaple
		for(int k=0; k<m; k++){

			//2.Feedforward
			printf("l=1\n");
			for (int i=0; i<xdim; i++){
				printf("%lf\n",x[i][k]);
			}

			printf("l=2\n");
			for(int i =0; i<l2no; i++){
				for(int j=0; j<xdim; j++){
					a1[i][k]+=w1[i][j]*x[j][k];
				}
				a1[i][k]+=b1[i];
				p1[i][k]=activation_derivative(a1[i][k]);
				a1[i][k]=activation(a1[i][k]);
				printf("%lf\n", a1[i][k]);
			}

			printf("l=3\n");
			for(int i =0; i<ydim; i++){
				for(int j=0; j<l2no; j++){
					ao[i][k]+=wo[i][j]*x[j][k];
				}
				ao[i][k]+=bo[i];
				po[i][k]=activation_derivative(ao[i][k]);
				ao[i][k]=activation(ao[i][k]);
				printf("%lf\n", ao[i][k]);
			}

			//3.Output error
			printf("delta of l=3\n");
			for(int i =0; i<ydim; i++){
				//printf("%lf %lf\n", ao[i][0], eo[i][0]);
				//printf("%lf\n", (ao[i][0]-y[i][0]));

				eo[i][k]=po[i][k]*2*(ao[i][k]-y[i][k]);
				printf("%lf\n", eo[i][k]);
			}

			//4.Backpropagate the error
			printf("delta of l=2\n");
			for(int i =0; i<l2no; i++){
				for (int j=0; j<ydim; j++){
					e1[i][k]+=wo[j][i]*eo[j][k]*p1[i][k];
				}
				printf("%lf\n", e1[i][k]);
			}
		}

		//5. Gradient descent
		descent(w1,b1,x,e1,
				wo,bo,a1,eo);
	}

	return 0;
}


double activation(double u){
	return 1.0/(1.0+exp(-u));
}

double activation_derivative(double u){
	return exp(-u)/pow((1.0+exp(-u)),2);
}

void randomize(double w1[l2no][xdim], double b1[l2no], double wo[ydim][l2no], double bo[ydim]){
	for(int i=0; i<l2no; i++){
		for(int j=0; j<xdim; j++){
			w1[i][j]=(double)rand()/RAND_MAX;
			//printf("%lf\n", w1[i][j]);
		}
	}

	for(int i=0; i<l2no; i++){
		b1[i]=(double)rand()/RAND_MAX;
	}

	for(int i=0; i<ydim; i++){
		for(int j=0; j<l2no; j++){
			wo[i][j]=(double)rand()/RAND_MAX;
		}
	}

	for(int i=0; i<ydim; i++){
		bo[i]=(double)rand()/RAND_MAX;
	}
}

void descent(double w1[l2no][xdim], double b1[l2no], double x[xdim][m], double e1[l2no][m],
			double wo[ydim][l2no], double bo[ydim], double a1[l2no][m], double eo[ydim][m]){
	for(int i=0; i<l2no; i++){
		for(int j=0; j<xdim; j++){
			for(int k=0; k<m; k++){
				w1[i][j]-=(lrate/m)*e1[i][k]*x[j][k];				
			}
		}
	}

	for(int i=0; i<l2no; i++){
		for(int k=0; k<m; k++){
			b1[i]-=(lrate/m)*e1[i][k];
		}
	}

	for(int i=0; i<ydim; i++){
		for(int j=0; j<l2no; j++){
			for(int k=0; k<m; k++){
				wo[i][j]-=(lrate/m)*eo[i][k]*a1[j][k];
			}
		}
	}

	for(int i=0; i<ydim; i++){
		for(int k=0; k<m; k++){
			bo[i]-=(lrate/m)*eo[i][k];
		}
	}
}