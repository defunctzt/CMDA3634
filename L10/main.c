#include "mympi.h"

int main(int argc, char ** argv)
{
	MPI_Init(&argc, &argv);
	int rank;
	int size;
	int N;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0)
	{
		N = 199; // Only rank 0 fills a value.
	}

	//myMPI_Bcast(&N,0);
	
	// This is the actual MPI Broadcast function
	MPI_Bcast(&N, // pointer to data
			   1, // count (number of entries)
			   MPI_INT, // data type
			   0, // root process (the process that broadcasts
			   MPI_COMM_WORLD);

	printf("Rank %d recieved the value N = %d.\n", rank, N);

	if (rank == size-1)
	{
		N = 10;

	}//end if

	MPI_Bcast(&N, // pointer to data
			   1, // count (number of entries)
			   MPI_INT, // data type
			   size-1, // root process (the process that broadcasts
			   MPI_COMM_WORLD);
	printf("Rank %d recieved the value of N = %d.\n", rank, N);

	// MPI's barrier
	MPI_Barrier(MPI_COMM_WORLD);

	// Set up a test for the reduction.
	float val = 1.0;
	float sum;
	// MPI's reduce function
	MPI_Reduce(&val, //send buffer
			   &sum, //recieve buffer
			   1, // count
			   MPI_FLOAT, //data type
			   MPI_SUM, //operation - others are MPI_MIN, MPI_MAX, MPI_PROD
			   0, //root process (the process that has the final answer)
			   MPI_COMM_WORLD);
	
	// This performs the reduction so all ranks have the final value.
	MPI_Allreduce(&val, // pointer to the value
				  &sum, // pointer to recieve
				  1, // count
				  MPI_FLOAT, // data type
				  MPI_SUM, // function
				  MPI_COMM_WORLD);

	for (int r = 0; r < size; r++)
	{
		if (r==rank)
		{
			printf("Rank %d has value %f after the reduction.\n", rank, sum);
		}//end if
		MPI_Barrier(MPI_COMM_WORLD);
	}//end for

	MPI_Finalize();
	return 0;
}//end main

