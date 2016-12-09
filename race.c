// Assignment 6 - Last assignment!

// This program lets the user race against four AI opponents by pressing enter
// to move their car forward.  The AI opponents move forward one space after a random
// amount of time between 0 and 100 milliseconds.  The first car to move 40 spaces
// is the winner.

// Team members:
//David Seekatz				16das4 20037710
//Sean Eylott				13se18 10141657
//Simon Ungar        			14seau 10149546
//Brooke Resendes   			13brr2 10141112

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
	long carAINums = ((long)args);
	time_t t;
	srand((unsigned) time(&t));
	while (1) {
		if (AIcounters[carAINums] == 40) {
			pthread_exit(NULL);
		} // end conditional
		AIcounters[carAINums]++;
		int waitTime = (int)((float)rand())/((float)(RAND_MAX)) * 100; // wait time in milliseconds
		usleep(waitTime*1000); // usleep takes argument in microseconds
	} // end while loop
	pthread_exit(NULL);
} // end carAI

// User function
void *carUser(void *args) {
	char enter;
	while (1) {
		if (user == 40) {
			pthread_exit(NULL);
		} else if (scanf("%c",&enter)) {
			user++;
		} // end conditional
	} // end while loop
	pthread_exit(NULL);
} // end carUser

// Printing function
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
		if (user == 40) {
			printf("Player 1 Wins!\n");
			exit(0);
		} // end conditional
		for (i = 0; i < NUM_AI; i++) {
			if (AIcounters[i] == 40) {
				printf("Player %d Wins!\n",i+2);
				exit(0);
			} // end conditional
		} // end for loop
		printstuff(user, 1);
		for (i = 2; i < NUM_AI + 2; i++) {
			printstuff(AIcounters[i-2], i);
		} // end for loop
		usleep(20000);
		system("clear");
	} // end while loop
	pthread_exit(NULL);
} // end draw

// main function
int main() {
	// print starting conditions
	system("clear");
	printf("Welcome to CISC220 Racing Arena!\nHit enter to move forward\n");
	printstuff(user, 1);
	long i;
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
	errorCheck = pthread_create(threads, NULL, draw, (void *) i);
	if (errorCheck) {
		printf("ERROR: Return code from pthread_create() is %d\n", errorCheck);
		exit(-1);
	} // end conditional

	// Create user thread	
	errorCheck = pthread_create(threads, NULL, carUser, (void *) i);
	if (errorCheck) {
		printf("ERROR: Return code from pthread_create() is %d\n", errorCheck);
		exit(-1);
	} // end conditional
	
	// Create AI threads
	for (i = 0; i < NUM_AI; i++) {
		errorCheck = pthread_create(threads, NULL, carAI, (void *) i);
		if (errorCheck) {
			printf("ERROR: Return code from pthread_create() is %d\n", errorCheck);
			exit(-1);
		} // end conditional
	} // end for loop	

	// Close everything and exit
	pthread_exit(NULL);
	return 0;
} // end main
