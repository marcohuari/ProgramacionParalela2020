/*
 ============================================================================
 Name        : Determinante_Matriz.c
 Author      : Marco
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 7

double determinantOfMatrix(double A[N][N], int n);
double cofactor(double A[N][N], int b,int j);

int main (int argc, char *argv[]) {
	double totalDet=0;
	srand(time(NULL));
  int tid;
  double A[N][N];
  for(int i=0;i<N;i++){
  		for(int j=0;j<N;j++){
  			A[i][j]=rand()%6;
  		}
  	}
  printf("\nMatriz generada:\n");
  for(int i=0;i<N;i++){
  		for(int j=0;j<N;j++){
  			printf("%lf ",A[i][j]);
  		}
  		printf("\n");
  }
  	omp_set_num_threads(N);
	printf("\nResolviendo la determinate con %d hilos:\n",N);
  	#pragma omp parallel
 {

	 tid = omp_get_thread_num();
	 double cof=cofactor(A,N,tid);
	 #pragma omp critical
	 totalDet+=cof;

 }
 printf("\nDeterminate: %lf ",totalDet);
 return 0;
}

double determinantOfMatrix(double A[N][N], int n)
{
	int index;
	double num1,num2,det = 1.0;
	double temp[n + 1];
	for(int i = 0; i < n; i++)
	{
		index = i;

		while(A[index][i] == 0 && index < n) {
			index++;

		}
		if(index == n)
		{
			continue;

		}
		if(index != i)
		{
			for(int j = 0; j < n; j++)
			{
				int aux=A[index][j];
				A[index][j]=A[i][j];
				A[i][j]=aux;
			}
				if((index-i)%2!=0){
					det*=-1;
				}
	}

	for(int j = 0; j < n; j++)
	{
		temp[j] = A[i][j];

	}
	for(int j = i+1; j < n; j++)
	{
		num1 = temp[i];
		num2 = A[j][i];

		for(int k = 0; k < n; k++)
		{
			A[j][k] = ((num1 * A[j][k]) - (num2 * temp[k]))/num1;

		}
		}

	}

	for(int i = 0; i < n; i++)
	{
		det = det * A[i][i];
	}

	return (det);
}

double cofactor(double A[N][N], int b,int j){
	double menor[b][b];
	int c;
	for(int i=0;i<b;i++){
			for(int j=0;j<b;j++){
				menor[i][j]=0;
			}
		}

	for(int k=1; k<b; k++){

			c = 0;

			for(int l=0; l<b; l++){

					if(l!=j){

							menor[k-1][c] = A[k][l];

							c++;

					}

			}

	}
	double determinant = A[0][j]*determinantOfMatrix(menor,b-1);
	printf("Resultado calculado por hilo es %d: %lf \n",j,determinant);
	if(j%2!=0)
		determinant*=-1;
	return determinant;
}
