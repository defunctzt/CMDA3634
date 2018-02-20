#include "mympi.h"

void myMPI_Bcast(int *N, int root);
void myMPI_Barrier();

/**
 * Broadcasts a message to other ranks.
 * @param *N the message received.
 * @root The one rank that isn't a sender in the broadcast.
**/
void myMPI_Bcast(int *N, int root)
{
	// Grab current rank and store it in rank.
	int rank;
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	// Every rank other than 0 recieves
	if (rank != root)
	{
		MPI_Status status;
		int tag = 1;

		int sourceRank = rank - 1; // Recieve from previous rank.

		// Guard against the case when rank = 0.
		if (rank == 0)
		{
			sourceRank = size-1;
		}
		MPI_Recv(N, // pointer to rank
				 1, // Number of values to recieve
				 MPI_INT, // Data type
				 sourceRank, // Where it's coming from.
				 tag,
				 MPI_COMM_WORLD,
				 &status);
	}//end if
	
	int prev = root-1; // Node before the root node.

	// Guard against rank 0 case.
	if (root == 0)
	{
		prev = size-1;
	}
	if (rank != prev)
	{
		int tag = 1;
		int destRank = rank+1; // Send to next rank.

		// Loop around if rank is the last size-1. Loop back to 0.
		if (rank == size-1)
		{
			destRank = 0;
		}
		// Send data
		MPI_Send(N,
				 1,
				 MPI_INT,
				 destRank,
				 tag,
				 MPI_COMM_WORLD);
	}//end if
}//end mpMPI_Bcast

/**
 * This acts as a barrier. No process can leave this function unless
 * ALL processes have made it here.
**/
void myMPI_Barrier()
{
	int N;
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0)
	{
		N = 1;
	}//end if
	if (rank == size - 1)
	{
		N = 10;
	}//end if
	myMPI_Bcast(&N, size-1);
}//end myMPIBarrier()
