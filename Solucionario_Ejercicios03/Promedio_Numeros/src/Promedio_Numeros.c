/*
 ============================================================================
 Name        : Promedio_Numeros.c
 Author      : Marco
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

long long *A = NULL;
float suma=0;
void LLenar();

int main(int argc, char *argv[]) {
	int n;
	scanf("%d",&n);
	A= (long long *) malloc (sizeof(long long)*n);
	printf("\n 01 Fuera de la region Paralela ...\n");

	LLenar(n);
	omp_set_num_threads(4);

	#pragma omp parallel
	{
		int local=0;
		int id = omp_get_thread_num();
		int nt = omp_get_num_threads();
		int nums=n/nt;
		int inicio=id*nums;
		int final=inicio+nums;

		for(int i=inicio;i<final;i++)
		{
			local+=A[i];
		}
		#pragma omp critical
		suma+=local;

		printf("\n HW desde el hilo %d de un total %d \n", id,	nt);
	}


	printf("Promedio: %f",suma/(n*1.0));


	printf("\n 02 Fuera de la region Paralela ...\n");
	return 0;
}

void LLenar(int n){

	for(int i=0;i<n;i++)
	{
		A[i]=i+1;
	}
}
