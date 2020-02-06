/*
 ============================================================================
 Name        : Pregunta_6.c
 author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : 
 ============================================================================
 */
#include <math.h> 
#include "mpi.h" 
#include <iostream>
#define n 20
using namespace std;
 
int main(int argc, char *argv[]) {
	int tamanio, rango,contador,coincidencias;
	int a[n]={0};
	int b[5]={0};

	MPI_Init(&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&tamanio);
	MPI_Comm_rank(MPI_COMM_WORLD,&rango);

	if(rango==0){
	for(int i=0;i<n;i++){
		a[i]=rand()%10;
	}
	}

	MPI_Scatter(&a,5,MPI_INT,&b,5,MPI_INT,0,MPI_COMM_WORLD);

	cout<<"Proceso "<<rango<<endl;
	for(int j=0;j<5;j++) cout<<b[j]<<" ";
	cout<<endl;

	contador=0;
	for(int k=0;k<5;k++){
		if(b[k]==5) contador++;
	}
	cout<<contador<<" coincidencia"<<endl;
	MPI_Reduce(&contador,&coincidencias,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

	if(rango==0){
	cout<<"La cantidad total de coincidencias es: "<<coincidencias<<endl;
	}

	MPI_Finalize();

	return 0;
}

