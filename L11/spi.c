#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char **argv) {
	MPI_Status status;
	MPI_Init(&argc, &argv);
	int rank, size;
	double estimate, rep;
	estimate = 0;
	rep = 0;
	double pi = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

//need running tallies
  long long int Ntotal;
  long long int Ncircle;

  //seed random number generator.
  srand48(rank);
	  
	
  for (long long int n=0; n<1000000000;n++) {
    //gererate two random numbers
    double rand1 = drand48(); //drand48 returns a number between 0 and 1
    double rand2 = drand48();
    
    double x = -1 + 2*rand1; //shift to [-1,1]
    double y = -1 + 2*rand2;

    //check if its in the circle
    if (sqrt(x*x+y*y)<=1) Ncircle++;
    Ntotal++;
  }
	rep = Ncircle/(double) Ntotal;
	MPI_Allreduce(&rep, &pi, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD); 
	pi = pi/size;

	if (rank == 0 && Ntotal % 100 == 0)
	{
 		 pi = 4.0*Ncircle/ (double) Ntotal;
		 printf("Our estimate of pi is %f \n", pi);
    }
	 MPI_Barrier(MPI_COMM_WORLD);

	 if (rank == 0)
	 {
    	 printf("Our estimate of pi is %f \n",4*pi);
	 }


  MPI_Finalize();

  return 0;
}
