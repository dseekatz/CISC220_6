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
			printf("Player %d Wins!\n",carAINums+1);
			exit(0);
		} // end conditional
		AIcounters[carAINums]++;
		int waitTime = rand() % 100;
		usleep(waitTime*10000);
	} // end while loop
	pthread_exit(NULL);
} // end carAI

// User function
void *carUser(void *args) {
	// Code for user car
	pthread_exit(NULL);
} // end carUser

void printstuff(int progress, int laneNum) {
	
	char carNumber[4];
	sprintf(carNumber,"%d #",laneNum);
	char lane[54] = "# Lane ";
	char aCar[] = "|->";
	char travel[] = "~";
	char blank[54] = "";
	char distance[54] = "";

	for (int i = 0 ; i < progress ; i++) {
		strcat(blank, travel);
	}

	for (int i = 0; i < 40 - progress ; i++) {
		strcat(distance, " ");
	}
	strcat(blank, aCar);
	strcat(blank, distance);
	strcat(blank, lane);
	strcat(blank, carNumber);
	printf("\n%s\n", blank);
}

// Draw function
void *draw(void *args) {
	int i = 0;
	while(1) {
		printstuff(user, 1);
		for (i = 2; i < NUM_AI + 2; i++) {
			printstuff(AIcounters[i-2], i);
		} // end for loop
		usleep(20000);
		system("clear");
	} // end while loop
	pthread_exit(NULL);
} // end draw

int main() {
	// print starting conditions
	system("clear");
	printf("Welcome to CISC220 Racing Arena!\nHit enter to move forward\n");
	printstuff(39, 1);
	int i;
	for (i = 2; i < NUM_AI + 2; i++) {
		printstuff(AIcounters[i-2], i);
	} // end for loop

	// Initialize threads and other variables
	pthread_t threads[NUM_AI + 2];
	int errorCheck;

	// Make sure the user starts the game
	char hitEnter;
	scanf("%c",&hitEnter);

	// Create drawing thread	
	printf("In main: creating drawing thread\n");
	errorCheck = pthread_create(threads, NULL, draw, (void *) &i);
	if (errorCheck) {
		printf("ERROR: Return code from pthread_create() is %d\n", errorCheck);
		exit(-1);
	} // end conditional

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

	// Close everything and exit
	pthread_exit(NULL);
	return 0;
} // end main
