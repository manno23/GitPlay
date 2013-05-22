rsa: rsa.c
	gcc -Wall -std=c99 -o rsa rsa.c -lm

clean:
	rm ./rsa

