#include <stdio.h>
#include <stdlib.h>

#define GENMAX 1000
#define NODENO 15
#define ALPHA 0.1
#define GAMMA 0.9
#define EPSILON 0.3
#define SEED 32767

int rand100();
int rand01();
double rand1();
void printqvalue(int qvalue[NODENO]);
int selecta(int s, int qvalue[NODENO]);
int updateq(int s, int qvalue[NODENO]);

int main(int argc, char const *argv[])
{
	int i;
	int s;
	int t;
	int qvalue[NODENO];
	srand(SEED);

	for (i=0; i<NODENO;++i){
		qvalue[i]=rand100();
	}
	printqvalue(qvalue);

	for (i=0; i<GENMAX;++i){
		s=0;
		for (t=0; t<3; ++t){
			s=selecta(s,qvalue); // 실제 행동

			qvalue[s]=updateq(s,qvalue); // 이때까지 행동을 바탕으로 Q-value 업데이트

		}
		printqvalue(qvalue);
	}
	return 0;
}

int updateq(int s, int qvalue[NODENO]){
	int qv;
	int qmax;

	if(s>6){
		if(s==14){
			qv=qvalue[s]+ALPHA*(1000 - qvalue[s]); // ALPHA는 속도, 1000이 Maximum.
		}else if(s==11){
			qv=qvalue[s]+ALPHA*(500 - qvalue[s]);
		}else{
			qv=qvalue[s];
		}
	}else{
		if ((qvalue[2*s+1])>(qvalue[2*s+2])) // 둘 중 큰 값을 넣어준다
		{
			qmax=qvalue[2*s+1]; //왼쪽

		}else{
			qmax=qvalue[2*s+2]; //오른쪽
		}
		qv=qvalue[s]+ALPHA*(GAMMA*qmax- qvalue[s]); //qvalue 업데이트
	}
	return qv;
}

int selecta(int olds, int qvalue[NODENO]){
	int s;

	if(rand1()<EPSILON){ //0~1 사이의 랜덤#, 즉 EPSILON=0.3의 확률, e-greedy 
		if(rand01()==0) 
			s=2*olds+1;
		else s=2*olds+2;
	}
	else{
		if((qvalue[2*olds+1])>qvalue[2*olds+2])
			s=2*olds+1;
		else s=2*olds+2;
	}

	return s;
}

void printqvalue(int qvalue[NODENO]){
	int i;

	for (i=1;i<NODENO;++i){
		printf("%d\t",qvalue[i] );
	}

	printf("\n");
}

double rand1(){
	return (double)rand()/RAND_MAX;
}

int rand01(){
	int rnd;

	while((rnd=rand())==RAND_MAX);

	return (int)((double)rnd/RAND_MAX*2);
}

int rand100(){
	int rnd;

	while((rnd=rand())==RAND_MAX);

	return (int)((double)rnd/RAND_MAX*101);
}