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
	treeMPI_Bcast(&N);

	printf("Rank %d recieved the value N = %d.\n", rank, N);

	if (rank == size-1)
	{
		N = 10;

	}//end if
	myMPI_Bcast(&N, size-1);
	printf("Rank %d recieved the value of N = %d.\n", rank, N);

	myMPI_Barrier();

	// Set up a test for the reduction.
	float val = 1.0;

	float sum = MPI_Reduction(val);

	for (int r = 0; r < size; r++)
	{
		if (r==rank)
		{
			printf("Rank %d has value %f after the reduction.\n", rank, sum);
		}//end if
		myMPI_Barrier();
	}//end for

	MPI_Finalize();
	return 0;
}//end main

