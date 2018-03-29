#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "mpi.h"
#include "functions.h"

int main (int argc, char **argv) {

  MPI_Init(&argc,&argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  if (size<2) {
    printf("Need at least two ranks for this function.\n");
    MPI_Finalize();
    exit(-1);
  }

  //seed value for the randomizer 
  double seed = clock()+rank; //this will make your program run differently everytime
  //double seed = rank; //uncomment this and your program will behave the same everytime it's run

  srand(seed);
  
  //begin with rank 0 getting user's input
  unsigned int n;

	unsigned int p,g,h,x;
  /* Q1.2 alter so only Alice performs the ElGamal setup */
  if (rank == 0)
  {
  	  printf("Enter a number of bits: "); fflush(stdout);
      char status = scanf("%u",&n);

 	 //make sure the input makes sense
 	 if ((n<3)||(n>31)) {//Updated bounds. 2 is no good, 31 is actually ok
   	 printf("Unsupported bit size.\n");
   	 return 0;   
 	 }
  	/* Q1.3 Share the public key information */
 	 printf("\n");

	
  		//setup an ElGamal cryptosystem
  		setupElGamal(n,&p,&g,&h,&x);
	}//end if
	MPI_Bcast(&p,1,MPI_UNSIGNED,0,MPI_COMM_WORLD);
	MPI_Bcast(&g,1,MPI_UNSIGNED,0,MPI_COMM_WORLD);
	MPI_Bcast(&h,1,MPI_UNSIGNED,0,MPI_COMM_WORLD); 
  //make an array of messages to send/recv
  unsigned int Nmessages = 5;

  //storage for messages
  unsigned int *message = 
      (unsigned int *) malloc(Nmessages*sizeof(unsigned int)); 
  
  //storage for extra encryption coefficient 
  unsigned int *a = 
      (unsigned int *) malloc(Nmessages*sizeof(unsigned int)); 

	if (rank == 1)
	{
 		 //fill the messages with random elements of Z_p
  		printf("Bob's original messages are:    [ ");
  		for (unsigned int i=0;i<Nmessages;i++) {
    		message[i] = randXbitInt(32)%p;
    		printf("%u ", message[i]);
 		 }
 		 printf("]\n");

  		//Encrypt the message with rank 0's ElGamal cyrptographic system
  		printf("Bob's encrypted messages are:   [ ");
  		for (unsigned int i=0;i<Nmessages;i++) {
    		ElGamalEncrypt(message+i,a+i,p,g,h);
    		printf("(%u,%u) ", message[i], a[i]);
  		}
  			printf("]\n");

  		/* Q2.3 Have only Bob populate messages and then
    		send all the encrypted mesages to Alice (rank 0) */

		int destRank = 0; // Alice
		int tag = 0;

		MPI_Send(message, // Pointer to size of array
				  Nmessages, // Number of entries
				  MPI_UNSIGNED, // Type of data
				  destRank, // Destination
				  tag,
				  MPI_COMM_WORLD);

		// Now send the actual array
		MPI_Send(a, // Data to send
			      Nmessages, // Number of items to send.
				  MPI_UNSIGNED, //Data type
				  destRank,
				  tag, // Tag for message
				  MPI_COMM_WORLD);
					  
	}//end if

  /* Q2.3 Have Alice recv all the encrypted mesages 
    from Bob (rank 1) and then decrypt them */
	if (rank == 0)
	{
		// Initialize the things we'll need for Alice to recive the messages.
		int sourceRank = 1;
		int tag = 0;
		//MPI_Request reqs[2];
		MPI_Status status;

		MPI_Recv(message, // Recieve array size from sender
				  Nmessages, // Number of entries
				  MPI_UNSIGNED, //data type
				  sourceRank,
				  tag,
				  MPI_COMM_WORLD,
				  &status);
	    
		//tag = 1; // Change tag.
		// Store array
		MPI_Recv(a, // Pointer of where to store data
				  Nmessages, // Number of entries
				  MPI_UNSIGNED, // Data type
				  sourceRank, // Rank of sender
				  tag,
				  MPI_COMM_WORLD,
				  &status);

		printf("Alice's recieved messages are:  [ ");
  		for (unsigned int i=0;i<Nmessages;i++) {
    		printf("(%u,%u) ", message[i],a[i]);
  		}
  		printf("]\n");

  		//Decrypt the message with rank 0's ElGamal cyrptographic system
  		printf("Alice's decrypted messages are: [ ");
  		for (unsigned int i=0;i<Nmessages;i++) {
    		ElGamalDecrypt(message+i,a[i],p,x);
    		printf("%u ", message[i]);
  		}
  		printf("]\n");
  		printf("\n");
	}//end if
  MPI_Finalize();

  return 0;
}
