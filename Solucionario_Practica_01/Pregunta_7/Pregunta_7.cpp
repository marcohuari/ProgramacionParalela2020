/*
 ============================================================================
 Name        : Pregunta_7.c
 author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : 
 ============================================================================
 */
#include <math.h> 
#include "mpi.h" 
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[]) {
	int tamanio, rango, producto,n,local_prod;
	int a[6]={0};
	int b[2]={0};

	MPI_Init(&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&tamanio);
	MPI_Comm_rank(MPI_COMM_WORLD,&rango);

	if(rango==0){
		cout<<"Ingrese número => ";cin>>n;
		for(int i=0;i<n;i++){
			a[i]=i+1;
		}
	}

	MPI_Scatter(&a,3,MPI_INT,&b,3,MPI_INT,0,MPI_COMM_WORLD);

	for(int j=0;j<3;j++){
		cout<<b[j]<<" ";
	}

	local_prod=b[0];
	for(int k=1;k<3;k++){
		local_prod*=b[k];
	}

	MPI_Reduce(&local_prod,&producto,1,MPI_INT,MPI_PROD,0,MPI_COMM_WORLD);

	if(rango==0){
		cout<<"El factorial del numero "<<n<<" es: "<<producto<<endl;
	}

	MPI_Finalize();
	return 0;
}

