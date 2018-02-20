/**
 * Make broadcast via binary tree.
**/

#include "mympi.h"

void treeMPI_Bcast(int *N)
{


	// Get the rank of this MPI process and total number of ranks.
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int Nactive = 1; // Only one rank active to start.

	// While not all ranks have the message.
	while (Nactive < size)
	{
		// ranks < Nactive send the value
		if (rank < Nactive)
		{
			//MPI_Send to rank + Nactive
			int destRank = rank + Nactive;
			if (destRank < size)
			{
				int tag = Nactive;
				MPI_Send(N,
					 	 1,
					 	 MPI_INT,
					 	 destRank,
					 	 tag,
					 	 MPI_COMM_WORLD);
			}//end if
		}//end if
		if ((rank >= Nactive) && (rank < 2*Nactive))
		{
			//MPI_Recv from rank - Nactive
			int sourceRank = rank - Nactive;
			int tag = Nactive;
			MPI_Status status;
			MPI_Recv(N,
					  1,
					  MPI_INT,
					  sourceRank,
					  tag,
					  MPI_COMM_WORLD,
					  &status);
		}//end if
		Nactive = Nactive * 2; // Double number of ranks that are active.
	}//end while
}// end treeMPI_Bcast
