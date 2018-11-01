/*
 * bfs.c
 *
 *  Created on: Oct 31, 2018
 *      Author: root
 */
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "bfs.h"

struct list_element_t_struct;
struct list_element_t_struct{
    int rank;
    struct list_element_t_struct* next;
};

typedef struct list_element_t_struct list_element_t;
typedef struct {
    list_element_t *head;
    list_element_t *tail;
}list_t;

list_t init_list();
void push_back(list_t* list, int rank);
void free_list(list_t *list);
int remove_front(list_t* list);
void push_front(list_t* list, int rank);
void fill_neighbors(int neighbors[], int rank);


int test_main(){
    list_t l1;
    l1 = init_list();
    assert(l1.head == l1.tail && l1.head == NULL);
    push_back(&l1, 10);
    assert(l1.head != NULL);
    assert(l1.tail == l1.head);
    assert(l1.head->rank == 10);
    assert(l1.head->next == NULL);

    push_back(&l1, 20);
    //the original cases 3 and 5 were different
    //they didn't make sense though
    assert(l1.head != l1.tail);
    assert(l1.head->rank == 10);
    assert(l1.head->next == NULL);
    assert(l1.tail->rank == 20);
    assert(l1.tail->next == l1.head);

    //free_list(&l1);
    remove_front(&l1);
    assert(l1.head == l1.tail);
    remove_front(&l1);
    assert(l1.head == l1.tail && l1.head == NULL);

    push_front(&l1, 20);
    assert(l1.head == l1.head && l1.head->rank == 20);
    assert(l1.head->next == NULL);

    push_front(&l1, 10);
    assert(l1.head != l1.tail);
    assert(l1.tail->rank == 20);
    assert(l1.head->rank == 10);
    assert(l1.head->next == NULL);
    assert(l1.tail->next == l1.head);

    int temp[5];
    fill_neighbors(temp, l1.head->rank);
    assert(temp[0] == 11);
    assert(temp[1] == -1);
    assert(temp[2] == 0);
    assert(temp[3] == 20);
    return 0;
}

list_t init_list(){
    list_t t;
    t.head = NULL;
    t.tail = NULL;
    return t;
}

void push_back(list_t* list, int rank){
    list_element_t* tmp = (list_element_t*)malloc(sizeof(list_element_t));
    assert(tmp != NULL);
    tmp->rank = rank;
    tmp->next = NULL;
    if(list->head == NULL && list->tail == NULL){
        list->head = tmp;
        list->tail = tmp;
    }
    else{
        tmp->next = list->tail;
        list->tail = tmp;
    }
}

void free_list(list_t *list){
    list_element_t* nxt = list->tail;
    while(nxt != NULL){
        list_element_t* tmp = nxt->next;
        free(nxt);
        nxt = tmp;
    }
    *list = init_list();
}

int remove_front(list_t* list){
    if(list->head == list->tail && list->head == NULL){
        return -1;
    }
    else if(list->head == list->tail){
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        *list = init_list();
    }
    else{
        list_element_t* tmp = list->tail;
        while(tmp->next->next != NULL){
            tmp = tmp->next;
        }
        free(list->head);
        list->head = NULL;
        list->head = tmp;
        tmp->next = NULL;
    }
    return 0;
}

void push_front(list_t* list, int rank){
    list_element_t* tmp = (list_element_t*)malloc(sizeof(list_element_t));
    assert(tmp != NULL);
    tmp->rank = rank;
    tmp->next = NULL;
    if(list->head == list->tail && list->head == NULL){
        list->head = tmp;
        list->tail = tmp;
    }
    else{
        list->head->next = tmp;
        list->head = tmp;
    }

}

void fill_neighbors(int neighbors[], int rank){
    int col = COL(rank);
    int row = ROW(rank);

    int right, left, up, down;

    if(col == MAZE_WIDTH){
        right = -1;
    }
    else{
        right = RANK(row, col+1);
    }
    if(col == 0){
        left = -1;
    }
    else{
        left = RANK(row, col-1);
    }
    if(row == 0){
        up = -1;
    }
    else{
        up = RANK(row-1, col);
    }
    if(col == MAZE_WIDTH){
        down = -1;
    }
    else{
        down = RANK(row+1, col);
    }

    neighbors[0] = right;
    neighbors[1] = left;
    neighbors[2] = up;
    neighbors[3] = down;

}
