#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "counter.h"


/* structs */
typedef struct __my_args {
    counter_t* c;
    int max_counter;
} my_args;

/* start_routine header */
void* increment_count(void* args);

/* Global variables */
pthread_mutex_t global_lock; 

int main(int argc, char *argv[]) { 
    printf("hola");
    pthread_mutex_init(&global_lock, NULL);
    int MAXCNT = atoi(argv[1]);
    int NUMTHREADS = atoi(argv[2]);
    
    
    /* Declaration of struct timeval variables */
    struct timeval start, end;
    double time;
    
    /* Initializing counter */
    counter_t* counter = malloc(sizeof(*counter));
    
    init(&counter);
    my_args args = {c : &counter, max_counter: MAXCNT };
    
    /* Threads handlers */
    pthread_t threads[NUMTHREADS];


    /* Thread creation */
    


    /* Time starts counting */
    gettimeofday(&start, NULL);


    /* Creating a Threads */
    for(int i = 0; i < NUMTHREADS; i++){
        pthread_create(&threads[i], NULL, &increment_count,&args);
    }
   

    /* Threads joins */
    for (int j = 0; j < NUMTHREADS; j++){
        pthread_join(threads[j],NULL);
    }


    /* Time stops counting here */
    int end_count = get(&counter);
    printf("final counter %d: \n", end_count);
    


    /* get the end time */
    //gettimeofday(&end, NULL);
    

    /* get the elapset time (end_time - start_time) */
    //time = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000.0;


    /* print the results (number threads employed, counter value, elasep time) */
    printf("Nro hilos: %d | contador: %d | tiempo:\n",NUMTHREADS, end_count);


    return 0;
}

/* start_routine definition */
void* increment_count(void* arg){
    pthread_mutex_lock(&global_lock);
    my_args args = *(my_args *)arg;
    int current = get(args.c);
    printf("current %d\n",current);
    if(current < args.max_counter){
       for(int i = 0; i < 10000; i++) {
           increment(args.c);
       }
    }
    pthread_mutex_unlock(&global_lock);
}
