make: *.c
	gcc -Wall -g -o philosophers philosophers.c -lpthread
