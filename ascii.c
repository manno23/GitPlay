/*
 * =======================================================================
 *
 *       Filename:  ascii.c
 *
 *    Description:  Test program for various things as I learn of them.
 *
 *         Author:  Jason Manning (ERiS), jasonmanning23@gmail.c9m
 *
 * =======================================================================
 */
#include <stdio.h>

int main(int argc, const char *argv[])
{

	// Playing with bitoperations
	int b = 7;
	printf("%i ", b);
	b = b << 1;
	printf("%i ", b);
	b = b << 1;
	printf("%i ", b);
	b = b << 1;
	printf("%i ", b);

	if(7 & 1)
		printf("111 1");
	if(4 & 1)
		printf("100 1");
	if(2 & 1) 
		printf("10 1");

	printf("\n");

	if(0)
		printf("0");
	if(1)
		printf("1");
	if(2)
		printf("2");

	printf("\n");
	if(7 & 7)
		printf("111 111\n");
	if(4 & 4)
		printf("100 100\n");
	if(3 & 5)
		printf("011 101\n");
	if(1 & 4)
		printf("001 100\n");
	if(4 & 5)
		printf("100 101\n");

	b = 1 & 4;
	printf("%i", b);

}
