#include<stdio.h>
#include<stdlib.h>

// Function header for gcd function.
int64_t gcd(int64_t x, int64_t y);

/**
 * Main function. Asks user for two numbers as input,
 * and returns the greatest common divisor.
**/
int main()
{
	int64_t a;
	int64_t b;
	printf("Enter the first number:");
	scanf("%ld", &a);
	printf("Enter the second number:");
	scanf("%ld", &b);
	int64_t result = gcd(a,b);
	printf("The greatest common divisor of %ld and %ld is %ld.\n", a, b, result);
	return 0;
}//end main

/**
 * Helper function that calculates the greatest common divisor
 * of two given integers.
 * Efficency: This solution is y - O(log(a+b)). This will work pretty efficently until
 * prime numbers get really large.
**/
int64_t gcd(int64_t x, int64_t y)
{
	while (y != 0)
	{
		int64_t remainder = x % y;
		x = y;
		y = remainder;
	}//end while
	if (x < 0)
	{
		x = x*-1;
	}//end if
	return x;
}//end gcd
