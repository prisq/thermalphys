#include <stdio.h>
#include <math.h>
#define PI 3.14159
#define n 10000

int main(){
	double sum=0.0;

	for (int i=0; i<n; i++){
		sum+=PI/n*sin(i*PI/n);
	}
	printf("%lf\n",sum );
	return 0;
}