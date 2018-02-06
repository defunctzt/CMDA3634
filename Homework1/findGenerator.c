/**
* Find the generator of a prime number.
* @author Zorian Thornton
**/
#include<stdio.h>
#include<stdlib.h>

// Function header for findGenerator().
int findGenerator(int prime);
int isPrime(int num);

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
**/
int findGenerator(int prime)
{
	// Stuff here.

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
	for (int i = 0; i < num; i++)
	{
		if (n % i == 0)
		{
			return 1; // Not prime
		}
	}//end for
	return 0; // Is prime.

}//end isPrime
