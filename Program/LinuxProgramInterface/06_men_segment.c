#include <stdio.h>
#include <stdlib.h>

char globBuf[65536];		/* Unitialized data segment */
int primes[] = {2,3,5,7};	/* Initialized data segment */

static int square(int x)	/* Allocated in frame for square() */
{
	int result;		/* ALlocated in frame for square() */
	
	result = x*x;
	return result;		/* Return value passed via register */
}

static void doCalc(int val)	/* Allocated in frame for doCalc() */
{
	printf("The squre of %d is %d\n", val, square(val));
	
	if (val < 1000)
	{
		int i;		/* Allocated in frame for doCalc() */
		t = val * val * val;
		printf("The cube of %d is %d\n", val, t);
	}
}

int main(int argc, char* argv[])
{
	static int key = 9973;		/* Initialized data segment */
	static char mbuf[1024];		/* Uninialized data segment */
	char* p;			/* Allocated in frame for main() */
	
	p = malloc(1024);		/* Point to memory in heap segment */
	doCalc(key);
	exit(EXIT_SUCCESS);
}
