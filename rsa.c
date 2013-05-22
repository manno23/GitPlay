/*
 * =======================================================================
 *
 *       Filename:  rsa.c
 *
 *    Description:  A simple implementation of the RSA cipher. Keys are 
 *		    generated, and then the program uses these to encrypt
 *		    then decrypt the message.
 *
 *        Version:  1.0
 *        Created:  16/05/13 02:46:01
 *       Compiler:  gcc
 *
 *         Author:  Jason Manning (ERiS), jasonmanning23@gmail.cm
 *
 * =======================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "time.h"

#define BUF_SIZE 1024

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

int gcd(int a, int b) {
	if(b == 0) 
		return a;
	else 
		return gcd(b, a%b);
}

int rand_int(int l_bound, int u_bound, int seed) {

	u_bound = u_bound - l_bound;
	int div = RAND_MAX/(u_bound + 1);
	int value;

	do {
		srand(time(NULL)+seed);
		value = rand() / div;
	} while (value > u_bound);

	return value + l_bound;
}

long generate_primes(int seed) {

	int is_not_prime = 1;
	long p;

	do {
		p = (double)rand_int(1000,10000,seed);

		if(p%2 == 1) {	 //check if p is odd, if not try new value of p
			
			int exp = (p-1)/2;    //will always be an integer as p-1 will always be even
			for(int i=0; i<8; i++) {

				int a = rand_int(0,p,seed);

				int r = mod_exp(a, exp, p);
				if( (r == 1) | (r == -1) ) {
					if(i == 7)
						is_not_prime = 0;
				} 
			}
		}
	} while (is_not_prime);

	return p;
}

long long inverse_modulus(long long e, long long modulus) {
	long long a = e;
	long long b = modulus;

	int x = 0;
	int y = 1;
	int x0 = 1;
	int y0 = 0;

	int q, temp;

	while(b != 0) {
		q = a/b;
		temp = a %b;
		a = b; 
		b = temp;

		temp = x;
		x = x0 - q * x;
		x0 = temp;

		temp = y;
		y = y0 - q * y;
		y0 = temp;
	}

	if(x0 < 0) 
		x0 += modulus;

	return x0;
}

int generate_exponent(int totient, int modulus) {
	int e = rand_int(10, totient, 1111);
	while(1) {
		if(gcd(e,totient) == 1)
			return e;
		e = (e+1)%totient;
	}
	return e;
}

int readFile(FILE* fd, char** buffer) {
	int length = 0;
	int cap = BUF_SIZE;
	char buf[BUF_SIZE];
	int r;
	*buffer = malloc(BUF_SIZE * sizeof(char));
	while((r = fread(buf, sizeof(char), BUF_SIZE, fd)) > 0) {
		if(length + r >= cap) {
			cap *= 2;
			*buffer = realloc(*buffer,cap);
		}
		memcpy(&(*buffer)[length],buf,r);
		length += r;
	}
	/* place null character to signify end of message */
	(*buffer)[length] = '\0';
	length++;

	return length;
}

long long *RSAencode(long long length, char* plaintext, long long e, long long n) {
	long long *ciphertext = malloc((length) * sizeof(long long));
	for(int i=0; i<length; i++) {
		ciphertext[i] = mod_exp(plaintext[i], e, n);
	}
	return ciphertext;
}

char *RSAdecode(long long length, long long *ciphertext, long long d, long long n) { char *plaintext = malloc((length) * sizeof(char));
	for(int i=0; i<length; i++) {
		char p = mod_exp(ciphertext[i], d, n);
		plaintext[i] = p;
		if(plaintext[i] != '\0')
			printf("%c", plaintext[i]);
	}
	return plaintext;
}

int main(int argc, const char *argv[]) {

	long long p, q, n, totient_n, e, d;


	// Step 1 - Generate prime factors
	printf("Generating primes....\n");
	p = generate_primes(1337);  
	q = generate_primes(2323);
	printf("Prime factors are p:%llu, q:%llu\n", p, q);

	n = p * q;
	printf("Which gives a modulus of n:%llu\n", n);


	// Step 2 - Generate public key exponent e
	totient_n = (p-1) * (q-1);
	printf("Totient(n):%llu\n", totient_n);
	e = generate_exponent(totient_n, n);
	printf("The public exponent e has the value e:%llu\n", e);


	// Step 3 - Generate private key exponent d
	d = inverse_modulus(e, totient_n);
	printf("The private exponent d has the value d:%llu\n", d);
	

	long long *ciphertext;
	char *plaintext;
	char* buffer;
	int length;
	FILE *file;
	// Step 4 - Convert symbols from file read in to ASCII code
	file = fopen("testfile_SDES.txt", "r");
	if(file == NULL) {
		printf("File could not be opened");
		return -1;
	}
	length = readFile(file, &buffer);
	fclose(file);

	
	// Step 5 - Implement RSA encryption
	ciphertext = RSAencode(length, buffer, e, n);
	plaintext = RSAdecode(length, ciphertext, d, n);

	free(ciphertext);
	free(plaintext);
	free(buffer);
	return 0;
}


