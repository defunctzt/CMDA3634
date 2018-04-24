#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"

int main (int argc, char **argv) {

	//seed value for the randomizer 
  double seed = clock(); //this will make your program run differently everytime
  //double seed = 0; //uncomment this and your program will behave the same everytime it's run

  srand(seed);

  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));

  printf("Enter a message to encrypt: ");
  int stat = scanf (" %[^\n]%*c", message); //reads in a full line from terminal, including spaces

  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h;

  printf("Reading file.\n");

  /* Q2 Complete this function. Read in the public key data from public_key.txt,
    convert the string to elements of Z_p, encrypt them, and write the cyphertexts to 
    message.txt */
	
	FILE *file; // Pointer to the file we want to open.
	file = fopen("public_key.txt", "r"); // Open file in read mode.
	
	fscanf(file, "%u", &n); // scan in n
	fscanf(file, "%u", &p); // scan in p
	fscanf(file, "%u", &g); // scan in g
	fscanf(file, "%u", &h); // scan in h

	fclose(file);

	// Convert string to elements of Z_p
	unsigned int charsPerint = (n-1)/8;

	padString(message, charsPerint); // Pad string before encryption.
	unsigned int Nchars = strlen(message);
	unsigned int Nints = strlen(message)/charsPerint;

	// Create stroage for Zp
	unsigned int *Zp = malloc(Nints*sizeof(unsigned int));

	// Create stroage for extra encryption coefficent.
	unsigned int *a = malloc(Nints*sizeof(unsigned int));

	// Convert string to Z.
	convertStringToZ(message, Nchars, Zp, Nints);

	// Encrypt Zp.
	ElGamalEncrypt(Zp,a,Nints,p,g,h);

	// Write the cyphertexts to message.txt.
	FILE *results; // Pointer to file to be written to.
	
	results = fopen("message.txt", "w"); // Open a file to write to.

	fprintf(results, "%u\n", Nints); // Print size of Zp first
	for (int i = 0; i < Nints+1; i++)
	{
		fprintf(results, "%u %u\n", Zp[i], a[i]);
	}//end for
	
	fclose(results); // Close file.


  
  return 0;
}
