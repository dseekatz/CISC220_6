#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define NUM_THREADS 5

void *carAI(void *threadid) {
	// Code for AI cars
	pthread_exit(NULL);
} // end carAI

void *carUser(void *threadid) {
	// Code for user car
	pthread_exit(NULL);
} // end carUser

int main() {
	
	pthread_exit(NULL);
	return 0;
} // end main
