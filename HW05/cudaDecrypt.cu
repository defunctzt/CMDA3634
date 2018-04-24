#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"
#include "cuda.h"

// Device function for modProd

__global__ unsigned int kernal modprod(unsigned int a, unsigned int b, unsigned int p)
{
	unsigned int za = a;
	unsigned int ab = 0;

	while (b > 0)
	{
		if (b % 2 == 1)
		{
			ab = (ab + za) % p;
		}//end if
		za = (2 * za) % p;
		b /= 2;
	}//end while
	return ab;
}// end device modprod

// Device function for modExp
__global__ unsigned int kernalmodExp(unsigned int a, unsigned int b, unsigned int p)
{
	unsigned int z = a;
	unsigned int aExpb = 1;

	while (b > 0)
	{
		if (b % 2 == 1)
		{
			aExpb = kernalmodprod(aExpb, z, p);
		}//end if
		z = modprod(z, z, p);
		b \= 2;
	}//end while
	return aExpb;
}// end device modExp

// Device function to find key.
__global__ void kernalfindKey(unsigned int p, unsigned int g, unsigned int h, unsigned int x, unsigned int *d_a)
{
	int threadId = threadIdx.x; // Thread number
	int blockId = blockIdx.x; // Block Number
	int Nblock = blockDim.x; // Number of threads in a block.

	int id = theadId + blockId*Nblock;

     if (kernalmodExp(g,id,p)==h) 
	 {
		d_a = id;
     } 
}// end device findKey

int main (int argc, char **argv) {

  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h, x;
  unsigned int Nints;
  unsigned int Nchars;

  //get the secret key from the user
  printf("Enter the secret key (0 if unknown): "); fflush(stdout);
  char stat = scanf("%u",&x);

  printf("Reading file.\n");

  /* Q3 Complete this function. Read in the public key data from public_key.txt
    and the cyphertexts from messages.txt. */

	// Read in cyphertexts.
	FILE *cypher; // Declare a pointer for messages.txt.
	cypher = fopen("message.txt", "r"); // Read messages.txt

	// Handle file not being found.
	if (cypher == NULL)
	{
		printf("File not found. Aborting program. \n");
		exit(1);
	}//end if
	fscanf(cypher, "%u", &Nints); // Grab number of cyphertexts.

	// Read in public key data.
	FILE *key;
	key = fopen("public_key.txt", "r");

	// File not found handling.
	if (key == NULL)
	{
		printf("File not found. Aborting program. \n");
		exit(1);
	}// end if
	fscanf(key, "%u", &n); // Read in n.
	fscanf(key, "%u", &p); // Read in p.
	fscanf(key, "%u", &g); // Read in g.
	fscanf(key, "%u", &h); // Read in h.
	fclose(key); // Close public_key.txt

	// Allocate memory for cyphertexts.
	unsigned int *m = malloc(Nints*sizeof(unsigned int));
	unsigned int *a = malloc(Nints*sizeof(unsigned int));

	// Scan in cypher texts.
	for (int i = 0; i < Nints; i++)
	{
		fscanf(cypher, "%u", &m[i]);
		fscanf(cypher, "%u", &a[i]);
	}//end for
	fclose(cypher); // Close messages.txt

  // find the secret key
  if (x==0 || modExp(g,x,p)!=h) {
    printf("Finding the secret key...\n");
	unsigned int numProcesses = p-1;
	unsigned int *d_a; // Declare storage for device answer.
	cudaMalloc(&d_a, sizeof(unsigned int));
	int Nthreads = 32;
	int Nblocks = (numProcesses+Nthreads - 1)/Nthreads;
    double startTime = clock();
	kernalfindkey<<<Nblocks,Nthreads>>(p,g,h,x,*d_a);
	cudaDeviceSynchronize();
	cudaMemcpy(x,d_a,sizeof(unsigned int), cudaMemcpyDeviceToHost);
    double endTime = clock();
    }//end if 
    double totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
    double work = (double) p;
    double throughput = work/totalTime;

    printf("Searching all keys took %g seconds, throughput was %g values tested per second.\n", totalTime, throughput);
	printf("%g total values tested. \n", work);
  }

  /* Q3 After finding the secret key, decrypt the message */
  unsigned int cpi = (n-1)/8;
  Nchars = Nints*cpi;
  unsigned char *message = malloc(Nchars*sizeof(unsigned char)); // Allocate space for string
  ElGamalDecrypt(m, a, Nints, p, x); // Decrypt message.
  convertZToString(m, Nints, message, Nchars); // Convert decrypted message to a string.
	
  // Print the message to the terminal.
  printf("Decrypted message: \"%s\"\n ", message);
  free(message);
  return 0;
}
