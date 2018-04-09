#ifdef _WIN32
	char full_direct[100] = ".\\text.txt";
	char full_direct2[100] = ".\\textout.txt";
#else
	char full_direct[100] = "./text.txt";
	char full_direct2[100] = "./textout.txt";
#endif
#include "time_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#pragma warning(disable : 4996)
#define buff_size 10
	FILE *file;
	FILE *filedest;
	int i;
	int j;
typedef struct {
	char buf[10][2000];
	int in;
	int out;
	sem_t occupied;
	sem_t empty;
	sem_t buffer;
} sbuf_t;
	sbuf_t shared;
	void *copy();
	void *paste();
	void *manage_buffer();
int main(){
	file = fopen(full_direct, "r+");
		if(file == NULL){
		printf("Error Retrieving File \n");
		printf("Could not retrieve file from the following directory: %s \n", full_direct);
		exit(1);
		}
	filedest = fopen(full_direct2, "w+");
	pthread_t consumer, producer;
	pthread_attr_t attr;
	sem_init(&shared.occupied, 0, 1);
	sem_init(&shared.empty, 0, 0);
	sem_init(&shared.buffer, 0, buff_size);
	if((file != NULL) && (filedest != NULL)){
	pthread_create(&producer, NULL, copy, NULL);
	pthread_create(&consumer, NULL, paste, NULL);
	manage_buffer();
	copy();
	paste();
	}
return 0;
}
void *manage_buffer(){
		sem_post(&shared.buffer);//Manages the buffer size.
}
		
void *copy(){
	while((full_direct != NULL) && (full_direct2 != NULL)){
	start_timing();
	char line[2000];
	while(1){
	//start_timing();
		while(fgets(line, sizeof line, file) != NULL){
		//scanf(" %s ", &line);
		sem_wait(&shared.occupied);//If the spot is occupied, wait.
		strncpy(&shared.buf[i], line, sizeof(line));
		sem_post(&shared.empty);
		if(i == 9){
			i = -1;
		}
		i++;
	}
	if(fgets(line, sizeof line, file) == NULL){
		stop_timing();
		printf("The Wall Time was %lf seconds.\n", get_wall_clock_diff());
		printf("The CPU time was %lf seconds.\n", get_CPU_time_diff());
		fclose(file);
		fclose(filedest);
#ifdef _WIN32
		getch();
#endif
		exit(1);
	}
}
}
}

	

void *paste(){
	while((full_direct != NULL) && (full_direct2 != NULL)){
	while(1){
			sem_wait(&shared.empty);
			fputs(&shared.buf[j], filedest);
			sem_post(&shared.occupied);
			if(j == 9){
				j = -1;
			}
			j++;
		}
			
	}
}


















