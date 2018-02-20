#include "mympi.h"

/**
 * Compute the global sum of all of the values across all MPI ranks.
**/
float MPI_Reduction(float val)
{
	// Assume rank 0 gets the sum of everything.
	float sum = val; // Accumulator for every rank

	float recvBuffer; // Space for incoming values.

	int rank, size;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// Start with all ranks active.
	int Nactive = size;

	while (Nactive > 1)
	{
		if (rank >= (Nactive+1)/2)
		{
			//MPI_Send to rank - Nactive/2.
			int destRank = rank - (Nactive+1)/2;
			int tag = Nactive;

			MPI_Send(&sum,
					 1,
					 MPI_FLOAT,
					 destRank,
					 tag,
					 MPI_COMM_WORLD);
			
		}//end if
		if (rank < Nactive/2)
		{
			//MPI_recv from rank + Nactive/2.
			int sourceRank = rank + (Nactive+1)/2;
			int tag = Nactive;
			MPI_Status status;
			MPI_Recv(&recvBuffer,
					 1,
					 MPI_FLOAT,
					 sourceRank,
					 tag,
					 MPI_COMM_WORLD,
					 &status);


			// Increment sum.
			sum = sum + recvBuffer;
		}// end if

		// Half the ranks that are active for the next run.
		Nactive = (Nactive+1)/2;
	}//end while
	return sum;
}//end MPI_Reduction
