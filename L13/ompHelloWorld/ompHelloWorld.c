#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <omp.h>

int main(int argc, char **argv)
{
	// Number of parallel threads that OpenMP should use.
	int numThreads = 4;

	// Tell OpenMP to use numThreads threads.
	omp_set_num_threads(numThreads);


	#pragma omp parallel
	{
		int rank = omp_get_thread_num(); // Get thread rank.
		int size = omp_get_num_threads(); // Get number of threads.

		printf("Hello World from thread %d of %d!\n", rank, size);
	} // end of parallel portion
	return 0;
}//end main
