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
 * It makes use of the property that large numbers can be broken
 * into their products and the modulo taken of these individually.
 * This is significant in RSA as the modulo of extremely large exponents
 * are used for decryption/encryption.
 */

long long mod_exp(long long a, long long b, long long n) {
	
	long long f = 1;
	long long e = 4294967296;	//equal to 2^32, msb set to 1
	int i;
	for(i=32; i>=0; i--) {
		f = (f*f)%n;
		if(b & e) {				//bitmask to see if bit is set
			f = (f*a)%n;
		} else {
		}
		e = e/2;				//move set bit left 1 space 
	}
	return f;
}

int main(int argc, char** argv) {

	long long message, key, modulo;
	
	printf("Enter in parameters for a^b mod n... \n");
	printf("a: ");
	scanf("%llu", &message);
	printf("b: ");
	scanf("%llu", &key);
	printf("n: ");
	scanf("%llu", &modulo);

	printf("%llu^%llu mod %llu = ", message, key, modulo);
	long long out;
	out = mod_exp(message, key, modulo);
	printf("%llu\n", out);
	return 1;
}

