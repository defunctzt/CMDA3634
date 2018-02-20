#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#include "mpi.h"

int main(int argc, char** argv)
{
	// Initialize MPI. Pass pointers to arg count and args.
	MPI_Init(&argc, &argv);

	int rank; // Rank variable.
	int size; // Number of ranks in network.

	// MPI_COMM_WORLD gives rank of process across entire network.
	// Tells MPI to get the rank of this process globally and store
	// the result in the rank variable.
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// This tells MPI to get the total number of processes working.
	// And stores the result in size.
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank < 5)
	{
		printf("Hello World from rank %d of %d!\n", rank, size);
	}//end if
	else
	{
		printf("Hello again from rank %d of %d!\n", rank, size);
	}//end else


	// All MPI programs must end with a finalize.
	MPI_Finalize();
}//end main
