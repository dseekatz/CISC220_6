#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

void printstuff(int progress) {

char carNumber[] = "2 #";
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

int main() {
for (int i=0 ; i < 30 ; i++) {
	printstuff(i);
}

return 0;
}
