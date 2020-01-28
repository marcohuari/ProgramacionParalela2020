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
        printf("Puede correr con 4 procesos.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
 
    
    int root_rank = 0;
 
    
    int mi_rango;
    MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);
 
    
    int mi_valor = mi_rango + 1;
    int reduction_result = 0;
    MPI_Reduce(&mi_valor, &reduction_result, 1, MPI_INT, MPI_PROD, root_rank, MPI_COMM_WORLD);
 
    if(mi_rango == root_rank)
    {
        printf("El producto de todos los valores es %d.\n", reduction_result);
    }
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}
