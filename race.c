#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

#define NUM_AI 4

// Car Progress Counters (Global Variables)
int user = 0;
int AIcounters[4] = {0, 0, 0, 0};

// AI function
void *carAI(void *args) {
	int carAINums = *(int*)args;
	time_t t;
	srand((unsigned) time(&t));
	while (1) {
		if (AIcounters[carAINums] == 40) {
			printf("Player %d Wins!",carAINums+1);
			exit(0);
		} // end conditional
		AIcounters[carAINums]++;
		int waitTime = rand() % 100;
		usleep(waitTime*1000);
	} // end while loop
	pthread_exit(NULL);
} // end carAI

// User function
void *carUser(void *args) {
	// Code for user car
	pthread_exit(NULL);
} // end carUser

// Draw function
void *draw(void *args) {
	// Code for drawing thread
	pthread_exit(NULL);
} // end draw

int main() {
	// Initialize threads and other variables
	pthread_t threads[NUM_AI + 2];
	int i = 0;
	int errorCheck;

	// Create user thread	
	printf("In main: creating user thread\n");
	errorCheck = pthread_create(threads, NULL, carUser, (void *) &i);
	if (errorCheck) {
		printf("ERROR: Return code from pthread_create() is %d\n", errorCheck);
		exit(-1);
	} // end conditional
	
	// Create AI threads
	for (i = 0; i < NUM_AI; i++) {
		printf("In main: creating an AI thread\n");
		errorCheck = pthread_create(threads, NULL, carAI, (void *) &i);
		if (errorCheck) {
			printf("ERROR: Return code from pthread_create() is %d\n", errorCheck);
			exit(-1);
		} // end conditional
	} // end for loop	

	// Create drawing thread	
	printf("In main: creating drawing thread\n");
	errorCheck = pthread_create(threads, NULL, draw, (void *) &i);
	if (errorCheck) {
		printf("ERROR: Return code from pthread_create() is %d\n", errorCheck);
		exit(-1);
	} // end conditional

	// Close everything and exit
	pthread_exit(NULL);
	return 0;
} // end main
