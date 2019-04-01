#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include <time.h>

#define xdim 4 //l=1
#define l2no 3
#define ydim 3 //l=3
#define m 5 //m is # of training sets

#define lrate 0.5 //learning rate
#define iter 1000000 // # of iteration 
#define randmultiplier 0.1

double activation(double u);
double activation_derivative(double u);
void randomize(double w1[l2no][xdim], double b1[l2no], double wo[ydim][l2no], double bo[ydim]);
void descent(double w1[l2no][xdim], double b1[l2no], double a1[l2no][m], double e1[l2no][m],
			double wo[ydim][l2no], double bo[ydim], double a0[ydim][m], double e0[ydim][m]);

int main()
{
	srand(time(NULL));

	double w1[l2no][xdim];	  //weight matrix
	double b1[l2no];		  //bias vector

	double wo[ydim][l2no];
	double bo[ydim];

	randomize(w1,b1,wo,bo);

	for(int epoch=0; epoch<iter; epoch++){
		if(epoch==iter-1) printf("Epoch : %d\n", epoch);

		double x[xdim][m]={{0,0,1,1,1}, 
						   {0,1,0,1,0},
						   {0,1,0,1,1},
						   {0,0,1,0,1}};
		double y[ydim][m]={{0,0,0,1,1},
						   {0,1,1,1,1},
						   {0,0,0,0,0}};

		double a1[l2no][m]={0,};  //activation(z)
		double e1[l2no][m]={0,};  //delta
		double p1[l2no][m]={0,};  //activation_derivative(z)

		double ao[ydim][m]={0,};
		double eo[ydim][m]={0,};
		double po[ydim][m]={0,};

		for(int k=0; k<m; k++){
			for (int i=0; i<xdim; i++){
				//x[i][k]=activation(x[i][k]);
				//printf("%lf ",x[i][k]);
			}
			//printf("\n");

			for(int i =0; i<l2no; i++){
				for(int j=0; j<xdim; j++){
					a1[i][k]+=w1[i][j]*x[j][k];
				}
				a1[i][k]+=b1[i];
				p1[i][k]=activation_derivative(a1[i][k]);
				a1[i][k]=activation(a1[i][k]);
				//if (k==0) printf("%lf ", a1[i][k]);
			}

			for(int i =0; i<ydim; i++){
				for(int j=0; j<l2no; j++){
					ao[i][k]+=wo[i][j]*a1[j][k];
				}
				ao[i][k]+=bo[i];
				po[i][k]=activation_derivative(ao[i][k]);
				ao[i][k]=activation(ao[i][k]);
				//if (k==0) 
				if(epoch==iter-1) printf("%lf ", ao[i][k]);
			}
			if(epoch==iter-1) printf("\n");

			for(int i =0; i<ydim; i++){
				eo[i][k]=2*(ao[i][k]-y[i][k])*po[i][k]; // gradient of cost ft * delta
			}

			for(int i =0; i<l2no; i++){
				for (int j=0; j<ydim; j++){
					e1[i][k]+=wo[j][i]*eo[j][k]*p1[i][k];
				}
			}

		}
		descent(w1,b1,x,e1,
				wo,bo,a1,eo);

	}
	printf("%lf\n", activation(0.000));

	//test data

	double tx[xdim]={1,
					 0,
					 1,
					 0}; //1*1 = 1
	double ta1[l2no]={0,};
	double tao[ydim]={0,};

	for(int i =0; i<l2no; i++){
		for(int j=0; j<xdim; j++){
			ta1[i]+=w1[i][j]*tx[j];
		}
		tao[i]+=bo[i];
		tao[i]=activation(tao[i]);
	}

	for(int i =0; i<ydim; i++){
		for(int j=0; j<l2no; j++){
			tao[i]+=wo[i][j]*ta1[j];
		}
		tao[i]+=bo[i];
		tao[i]=activation(tao[i]);
		//if (k==0) 
		printf("%lf ", tao[i]);
	}
	printf("\n");
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
			w1[i][j]=(double)rand()/RAND_MAX*randmultiplier;
			printf("%lf ", w1[i][j]);
		}
		printf("\n");
	}

	for(int i=0; i<l2no; i++){
		b1[i]=(double)rand()/RAND_MAX*randmultiplier;
		printf("%lf ", b1[i]);
	}
	printf("\n\n");

	for(int i=0; i<ydim; i++){
		for(int j=0; j<l2no; j++){
			wo[i][j]=(double)rand()/RAND_MAX*randmultiplier;
			printf("%lf ", wo[i][j]);
		}
		printf("\n");
	}

	for(int i=0; i<ydim; i++){
		bo[i]=(double)rand()/RAND_MAX*randmultiplier;
		printf("%lf ", bo[i]);
	}
	printf("\n");
}

void descent(double w1[l2no][xdim], double b1[l2no], double x[xdim][m], double e1[l2no][m],
			double wo[ydim][l2no], double bo[ydim], double a1[l2no][m], double eo[ydim][m]){
	for(int i=0; i<l2no; i++){
		for(int j=0; j<xdim; j++){
			for(int k=0; k<m; k++){
				w1[i][j]-=(lrate/m)*e1[i][k]*x[j][k];

			}
			//printf("%lf ", w1[i][j]);
		}
		//printf("\n");
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