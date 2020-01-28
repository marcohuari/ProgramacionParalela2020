#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4)
    {
        printf("Este programa corre con 4 procesos.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
 
    int root_rank = 0;
 
   
    int mi_rango;
    MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);
 
    int resultado_final = 0;
    MPI_Reduce(&mi_rango, &resultado_final, 1, MPI_INT, MPI_MIN, root_rank, MPI_COMM_WORLD);
 
    if(mi_rango == root_rank)
    {
        printf("El minimo de todas las posiciones es %d.\n", resultado_final
);
    }
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}
