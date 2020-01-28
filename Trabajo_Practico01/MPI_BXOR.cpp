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
        printf("Esta aplicacion debe ser corrida con 4 procesos.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
 
    
    int root_rank = 0;
 
    
    int mi_rango;
    MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);
 
    
    char all_values[4] = {0, 1, 3, 8};
    char my_value = all_values[mi_rango];
    char resultado_final = 0;
    MPI_Reduce(&my_value, &resultado_final, 1, MPI_UNSIGNED_CHAR, MPI_BXOR, root_rank, MPI_COMM_WORLD);
 
    if(mi_rango == root_rank)
    {
        printf("El bit exclusivo o de todos los valores %d.\n", resultado_final);
    }
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}
