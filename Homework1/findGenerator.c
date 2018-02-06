/**
* Find the generator of a prime number.
* @author Zorian Thornton
**/
#include<stdio.h>
#include<stdlib.h>

// Function header for findGenerator().
int findGenerator(int prime);
int isPrime(int num);
int power(int base, int power);

/**
* Main function that prompts a user to enter a prime number.
* Tells the user that the number is not prime if a non-prime number is entered.
* Returns a generator of Z_p if the number entered is prime.
**/
int main()
{
	// Allocate space from prime number.
	int p;
	printf("Enter a prime number: ");
	scanf("%d", &p);

	if (isPrime(p) == 1)
	{
		printf("%d is not a prime number.\n", p);
		return 0;
	}//end if

	// Find generator.
	int result = findGenerator(p);

	// Return the result.
	printf("%d is a generator of Z_%d.\n", result, p);

	// Return 0 if no errors.
	return 0;

}//end main

/**
 * Finds the generator of a given prime number.
 * @param prime	The prime number input by the user.
 * @return A generator found for Z_p.
 * Efficency: Long story short, this algorithm will take a LONG time. As prime number p grows larger,
 * this will take an exponentially longer time to run due to multiple loops.
**/
int findGenerator(int prime)
{
	// Initialize stuff.
	int limit = prime-1;
	int *set = (int*) malloc((limit)*sizeof(int));

	// Zero out array.
	for (int i = 0; i < limit; i++)
	{
		set[i] = 0;
	}//end for

	// Loof for generator
	for (int i = 2; i <= limit; i++)
	{
		for (int j = 1; j <= limit; j++)
		{
			int result = power(i,j);
			if (set[(result % prime)-1] == 0)
			{
				set[(result % prime)-1] = 1;
			}//end if
		}//end for
		int success = 0;
		// Check to see if array is filled.
		for (int k = 0; k < limit; k++)
		{
			if (set[k] == 1)
			{
				success++;
			}
		}//end for
		if (success == limit)
		{
			return i;
		}//end if

	}//end for


}//end findGenerator

/**
 * Determines if a number is prime or not.
 * @param	num	The number the user input.
 * @return 0 if the number is prime, 1 otherwise.
**/
int isPrime(int num)
{
	// Stuff here.
	if (num <= 1)
	{
		return 1;
	}//end if
	if (num == 2)
	{
		return 0;
	}//end if
	for (int i = 2; i < num; i++)
	{
		if (num % i == 0)
		{
			return 1; // Not prime
		}
	}//end for
	return 0; // Is prime.

}//end isPrime

/**
 * Raises a number to a power.
**/
int power(int base, int power)
{
	int res = 1;
	while (power != 0)
	{
		res = res * base;
		power--;
	}//end while
	return res;
}//end power
