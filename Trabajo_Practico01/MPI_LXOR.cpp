#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>
 
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
 
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4)
    {
        printf("Esta aplicacion corre con 4 procesos.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
 
    int root_rank = 0;
 

    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 
    bool mi_valor = (my_rank == 3);
    bool resultado_final = false;
    MPI_Reduce(&mi_valor, &resultado_final, 1, MPI_C_BOOL, MPI_LXOR, root_rank, MPI_COMM_WORLD);
 
    if(my_rank == root_rank)
    {
        printf("La logica exclusiva OR o de todos es %s.\n", resultado_final ? "true" : "false");
    }
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}
