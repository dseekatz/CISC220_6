#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

#define NUM_AI 4

void *carAI(void *aString) {
	char* str;
	str = (char*) aString;
	printf("%s\n", str);
	// Code for AI cars
	pthread_exit(NULL);
} // end carAI

void *carUser(void *aString) {
	char* str;
	str = (char*) aString;
	printf("%s\n", str);
	// Code for user car
	pthread_exit(NULL);
} // end carUser

int main() {
	// Initialize threads and other variables
	pthread_t threads[NUM_AI + 1];
	int i;
	int errorCheck;
	char str[54];
	strcpy(str, "|->                                        # Lane ");
	
	// Create user thread	
	printf("In main: creating user thread\n");
	errorCheck = pthread_create(threads, NULL, carUser, (void *) str);
	if (errorCheck) {
		printf("ERROR: Return code from pthread_create() is %d\n", errorCheck);
		exit(-1);
	} // end conditional
	
	// Create AI threads
	for (i = 0; i < NUM_AI; i++) {
		printf("In main: creating an AI thread\n");
		errorCheck = pthread_create(threads, NULL, carAI, (void *) str);
		if (errorCheck) {
			printf("ERROR: Return code from pthread_create() is %d\n", errorCheck);
			exit(-1);
		} // end conditional
	} // end for loop	
	
	// Close everything and exit
	pthread_exit(NULL);
	return 0;
} // end main
