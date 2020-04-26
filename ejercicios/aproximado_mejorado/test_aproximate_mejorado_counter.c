#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "counter.h"


void *increment_count(void *arg);

/* Global variables */
pthread_mutex_t global_lock;
counter_t counter;
int MAXCNT;
int NUMTHREADS;
int THRESHOLD;

int main(int argc, char *argv[]) { 
    pthread_mutex_init(&global_lock, NULL);
    MAXCNT = atoi(argv[1]);
    NUMTHREADS = atoi(argv[2]);
    THRESHOLD = atoi(argv[3]);
    
    
    /* Declaration of struct timeval variables */
    struct timeval start, end;
    long time;
    
    /* Initializing counter */
    
    
    init(&counter,THRESHOLD);
    
    /* Threads handlers */
    pthread_t threads[NUMTHREADS];


    /* Thread creation */
    


    /* Time starts counting */
    gettimeofday(&start, NULL);

    int ids[NUMTHREADS];
    /* Creating a Threads */
    for(int i = 0; i < NUMTHREADS; i++){
        ids[i] = i;
        pthread_create(&threads[i], NULL, increment_count,(void *)&ids[i]);
    }
   

    /* Threads joins */
    for (int j = 0; j < NUMTHREADS; j++){
        pthread_join(threads[j],NULL);
    }


    /* Time stops counting here */
    int end_count = get(&counter);
    printf("final counter: %d\n", end_count);
    


    /* get the end time */
    gettimeofday(&end, NULL);
    

    /* get the elapset time (end_time - start_time) */
    time = (end.tv_usec - start.tv_usec)/1000.0;


    /* print the results (number threads employed, counter value, elasep time) */
    printf("Nro hilos: %d | contador: %d | tiempo: %ld milisegundos \n",NUMTHREADS, end_count, time);


    return 0;
}

/* start_routine definition */
void *increment_count(void* arg){
    pthread_mutex_lock(&global_lock);
    int *id = (int *)arg;
    int threadID = *id;
  
    int current = get(&counter);
   
    if(current < MAXCNT){
       for(int i = 0; i < 1000000; i++) {
            update(&counter,threadID,1);
        }
    }
    pthread_mutex_unlock(&global_lock);
}