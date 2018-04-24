include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"


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
    double startTime = clock();
    for (unsigned int i=0;i<p-1;i++) {
      if (modExp(g,i+1,p)==h) {
        printf("Secret key found! x = %u \n", i+1);
        x=i+1;
      } 
    }
    double endTime = clock();

    double totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
    double work = (double) p;
    double throughput = work/totalTime;

    printf("Searching all keys took %g seconds, throughput was %g values tested per second.\n", totalTime, throughput);
	printf("%g total values tested. \n", work);
  }

  /* Q3 After finding the secret key, decrypt the message */
  unsigned int buffer = 1024;
  unsigned int cpi = (n-1)/8;
  Nchars = Nints*cpi;
  unsigned char *message = malloc(Nchars*sizeof(unsigned char)); // Allocate space for string
  ElGamalDecrypt(m, a, Nints, p, x); // Decrypt message.
  convertZToString(m, Nints, message, Nchars); // Convert decrypted message to a string.
	
  // Print the message to the terminal.
  printf("Decrypted message: \"%s\"\n ", message);
  /*
  for (int i = 0; i <= Nints; i++)
  {
  	printf("%c", message[i]);
  }//end for
  printf("\n");
  */
  free(message);
  return 0;
}
