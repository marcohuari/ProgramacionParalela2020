#define  LEN   1000 
 
float val[LEN];         
int count;             
int mi_rank, mini_rank, mini_index; 
float mini_val; 

 
struct { 
    float value; 
    int   index; 
} in, out; 

 
in.value = val[0]; 
in.index = 0; 
for (i=1; i < count; i++) 
    if (in.value > val[i]) { 
        in.value = val[i]; 
        in.index = i; 
    } 

 

MPI_Comm_rank(MPI_COMM_WORLD, &mi_rank); 
in.index = mi_rank*LEN + in.index; 
MPI_Reduce( in, out, 1, MPI_FLOAT_INT, MPI_MINLOC, root, comm ); 
   
if (mi_rank == root) { 
    
    mini_val = out.value; 
    mini_rank = out.index / LEN; 
    mini_index = out.index % LEN; 
} 
