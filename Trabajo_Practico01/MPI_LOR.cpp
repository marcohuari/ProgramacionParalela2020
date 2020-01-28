#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>
 
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
 
    
    int tamanio;
    MPI_Comm_tamanio(MPI_COMM_WORLD, &tamanio);
    if(tamanio != 4)
    {
        printf("Esta aplicacion debe ser corrida con 4 procesos.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
 
   
    int root_rank = 0;
 
    
    int mi_rango;
    MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);
 
    
    bool my_value = (mi_rango == 3);
    bool reduction_result = false;
    MPI_Reduce(&my_value, &reduction_result, 1, MPI_C_BOOL, MPI_LOR, root_rank, MPI_COMM_WORLD);
 
    if(mi_rango == root_rank)
    {
        printf("La logica de todos los valores son %s.\n", reduction_result ? "true" : "false");
    }
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}
