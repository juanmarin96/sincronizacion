#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "list.h"

void init_list(list_t *l) {
    l->head = NULL;
    pthread_mutex_init(&l->lock, NULL);
}

void init_book_catalog(list_t *l){
    printf("Initializing list of available books\n");
    for (int i = 0; i < 10000; i++)
    {
        char name[10];
        book *b = malloc(sizeof(book));
        sprintf(name, "book_%d", i);
        b->id = i;
        b->name = name;
        b->num_pages = 100;
        b->pub_year = 2020;
        list_insert(l,i,b);
    }
}

void list_insert(list_t *l, int key, book *b) {
    // synchronization not needed
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        perror("malloc");
        return;
    }
    new->key = key;
    new->book = b;
    new->next = l->head;
    new->available = 1;
    l->head = new;
 }

int loan_book(list_t *l, int key) {
    pthread_mutex_lock(&l->lock);
    int loaned = -1;
    node_t *curr = l->head;
    while (curr) {
        if (curr->key == key) {
            if(curr->available == 1){
                curr->available = 0;
                loaned = 1;
            }else{
                loaned = 0;
            }
            break;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&l->lock);
    return loaned;
}