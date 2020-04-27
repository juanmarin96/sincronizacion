#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "list.h"
//#include <time.h>
#include <sys/time.h>


typedef struct __results {
    int success_loans;
    int failed_loans;
} results;

typedef struct __office_args {
    int office_id;
    int seed;
    results *results;
} office_args;

list_t book_catalog;


/* Thread function */
void *loan_books(void *args);
int main(int argc, char *argv[]){
    
    /* Init list */
    init_list(&book_catalog);

    /* Init book catalog */
    init_book_catalog(&book_catalog);

    /* Declaring 4 officesa and its args */
    pthread_t offices[4];
    office_args *args[4];
    struct timeval start, end;
    double execution_time;
    int total_success = 0, total_fails = 0;

    /* Init args */
    for (int i = 0; i < 4; i++)
    {
        office_args *arg = malloc(sizeof(office_args));
        arg->office_id = i;
        arg->seed = (int)rand();
        arg->results = malloc(sizeof(results));
        args[i] = arg;
        printf("Office %d initialized with seed %d\n", i, arg->seed);
    }
    


    /* Time starts counting */
    gettimeofday(&start, NULL);

    /* Create threads */
    for (int i = 0; i < 4; i++)
    {
        pthread_create(&offices[i], NULL, &loan_books,args[i]);
    }
    

    /* End job */
    for (int j = 0; j < 4; j++)
    {
        pthread_join(offices[j], NULL);
        printf("Office %d has finished its workload, successful loans %d, failed loans %d\n",j,args[j]->results->success_loans,args[j]->results->failed_loans);
        total_success = total_success + args[j]->results->success_loans;
        total_fails = total_fails + args[j]->results->failed_loans;
    }
    
    
    /* get the end time */
    gettimeofday(&end, NULL);

    /* get the elapset time (end_time - start_time) */
    execution_time = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000.0;
    printf("Simulation done execution time: %g ms\n", execution_time);
    printf("Total successful loans %d, total failed loans %d\n",total_success, total_fails);
    printf("Number of remaining available books %d\n", 10000 - total_success);
    return 0;
}

void *loan_books(void *args){
    office_args office_arg= *((office_args *)args);
    int seed = office_arg.seed;
    srand(seed);
    for (int i = 0; i < 1000; i++)
    {
        int book_to_loan = rand() % (9999 + 1 - 0) + 0;
        int loaned = loan_book(&book_catalog,book_to_loan);
        if(loaned == 1){
            office_arg.results->success_loans++;
        }else{
            office_arg.results->failed_loans++;
        }
    }
    return 0;
}