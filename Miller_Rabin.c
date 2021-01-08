// C program Miller-Rabin primality test 
#include <stdio.h> 

// Utility function to do modular exponentiation. It returns (x^y) % p 
int power(int x, unsigned int y, int p) 
{ 
	int res = 1;	 
	x = x % p; 
	while (y > 0) 
	{ 
		if (y & 1) 
			res = (res*x) % p; 
		y = y>>1;
		x = (x*x) % p; 
	} 
	return res; 
} 

//Miller-Rabin Test for prime numbers
int millerTest(int d, int n) 
{ 
	int a = 2 + rand() % (n - 4); 
	int x = power(a, d, n); 
	if (x == 1 || x == n-1) 
	return 1; 
	while (d != n-1) 
	{ 
		x = (x * x) % n; 
		d *= 2; 

		if (x == 1)	 return 0; 
		if (x == n-1) return 1; 
	} 
	return 0; 
} 

//It returns false if n is composite and returns true if n is probably prime.  
//k is an input parameter that determines accuracy level.
//Higher value of k indicates more accuracy
int isPrime(int n, int k) 
{ 
	if (n <= 1 || n == 4) return 0; 
	if (n <= 3) return 1; 
	int d = n - 1; 
	while (d % 2 == 0) 
		d /= 2; 
	int  i;
	for (i = 0; i < k; i++) 
		if (!millerTest(d, n)) 
			return 0; 
	return 1; 
} 
