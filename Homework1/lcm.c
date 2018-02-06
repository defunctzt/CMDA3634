/**
 * Calculates least common multiple of two user inputted numbers.
 * @author Zorian Thornton
**/
#include<stdio.h>
#include<stdlib.h>

// Function headers for gcd and lcm.
int gcd(int x, int y);
int lcm(int x, int y);

/**
 * Main function that prompts the user to enter two numbers,
 * and then returns the lcm of these two numbers.
**/
int main()
{
	// Allocate memory for input.
	int a;
	int b;

	// Prompt user and store data.
	printf("Enter the first number: ");
	scanf("%d", &a);
	printf("Enter the second number: ");
	scanf("%d", &b);

	// Find lcm.
	int result = lcm(a,b);

	// Print the result.
	printf("The least common multiple of %d and %d is %d.\n", a, b, result);
	return 0;
}//end main

/**
 * Calculates the gcd of two integers.
 * Efficency: Stated multiple times before.
**/
int gcd(int x, int y)
{
	while (y != 0)
	{
		int remainder = x % y;
		x = y;
		y = remainder;
	}//end while
	
	// If x is negative, make it positive.
	if (x < 0)
	{
		x = x*-1;
	}//end if
	return x;
}//end gcd

/**
 * Calculates the lcm of two integers.
 * Efficency: Runs in constant time.
**/
int lcm(int x, int y)
{
	int top = x*y;
	int bottom = gcd(x,y);
	return top/bottom;
}//end lcm
