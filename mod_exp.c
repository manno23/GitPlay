/*
 * =======================================================================
 *
 *       Filename:  mod_exp.c
 *
 *    Description:  An implementation of RSA encryption, making use of
 *					modular arithemetic to reduce the large exponentiaition
 *					to a form that can be handled.
 *
 *        Version:  1.0
 *        Created:  05/05/13 18:15:42
 *       Compiler:  gcc
 *
 *         Author:  Jason Manning (ERiS), jasonmanning23@gmail.cm
 *
 * =======================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "math.h"
#include "string.h"


/*
 * Implementation as found on Cryptography and Network Security
 * pg. 283
 * It runs backward so as to allow for unknown bit size, and also 
 * for the ease of use of bitwise operators
 */

unsigned long mod_exp(unsigned long a, unsigned long b, unsigned long n) {
	
	unsigned long f = 1;
	unsigned long e = 1;
	int i;
	for(i=0; i<=32; i++) {
		f = (f*f)%n;
		if(b & e) 
			f = (f*a)%n;
		e << 1;
	}
	return f;
}

int main(int argc, char** argv) {

	unsigned long message, key, modulo;
	
	printf("Enter in parameters for a^b mod n... \n");
	printf("a: ");
	scanf("%lu", &message);
	printf("b: ");
	scanf("%lu", &key);
	printf("n: ");
	scanf("%lu", &modulo);

	printf("%lu^%lu mod %lu = ", message, key, modulo);
	unsigned long out;
	out = mod_exp(message, key, modulo);
	printf("%lu\n", out);
	return 1;
}

