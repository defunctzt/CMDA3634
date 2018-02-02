/**
 * This function will take two integers from a user's unput and return
 * whether they are coPrime or not. Coprime, by definition, is when 
 * two numbers have a GCD of 1.
 * @author	Zorian Thornton
**/
#include<stdio.h>
#include<stdlib.h>

// Function header for gcd.
int gcd(int x, int y);

/**
 * The main function for this program. 
 * Prompts the user to input two numbers.
 * Prints to the screen whether the numbers are coprime or not.
**/
int main()
{
	// Allocate space for user input.
	int firstInput;
	int secondInput;

	// Prompt user and store the data.
	printf("Enter the first number: ");
	scanf("%d", &firstInput);
	printf("Enter the second number: ");
	scanf("%d", &secondInput);
	if (gcd(firstInput, secondInput) == 1)
	{
		printf("%d and %d are coprime.\n", firstInput, secondInput);
	}//end if
	else
	{
		printf("%d and %d are not coprime.\n", firstInput, secondInput);
	}//end else
	return 0;
}//end main

/**
 * Calculates the gcd of two numbers.
 * @param x The first number to evaluate.
 * @param y The second number to evaluate.
 * @return The greatest common divsor of x and y.
**/
int gcd(int x, int y)
{
	while (y != 0)
	{
		int remainder = x % y;
		x = y;
		y = remainder;
	}//end while

	// Make positive if negative.
	if (x < 0)
	{
		x = x * -1;
	}//end if
	return x;
}//end gcd
