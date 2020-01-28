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
        printf("Esta aplicacion debe tener 4 procesos para que pueda funcionar.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
 
    int root_rank = 0;
 
    int mi_rango;
    MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);
 
    bool my_value = (mi_rango != 3);
    bool resultado_final = false;
    MPI_Reduce(&my_value, &resultado_final, 1, MPI_C_BOOL, MPI_LAND, root_rank, MPI_COMM_WORLD);
 
    if(mi_rango == root_rank)
    {
        printf("La logica and y de todos los valores es %s.\n", resultado_final ? "true" : "false");
    }
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}
