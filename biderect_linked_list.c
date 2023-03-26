/*
Bi-directional linked list
by Nicolas Dupuy
26 March, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

typedef struct bidirect_linked_list {
    struct bidirect_linked_list *prev;
    struct bidirect_linked_list *next;
    int data;
} bidirect_linked_list;

/*Create a new list*/
bidirect_linked_list *create_list(int data) {
    bidirect_linked_list *new_list = malloc(sizeof(bidirect_linked_list));
    new_list->prev = new_list->next = NULL;
    new_list->data = data;
    return new_list;
}

/*Returns the last node of the list*/
bidirect_linked_list *move_to_end(bidirect_linked_list * list){
    if(list->next)
        return(move_to_end(list->next));
    return list;
}

/*Returns the first node of the list*/
bidirect_linked_list *move_to_start(bidirect_linked_list * list){
    if(list->prev)
        return(move_to_start(list->prev));
    return list;     
}

void append_to_end(bidirect_linked_list *list, int data) {
    bidirect_linked_list *end = move_to_end(list);
    bidirect_linked_list *new_node = create_list(data);
    end->next = new_node;
    new_node->prev = end;
}

void append_to_start(bidirect_linked_list *list, int data) {
    bidirect_linked_list *start = move_to_start(list);
    bidirect_linked_list *new_node = create_list(data);
    start->prev = new_node;
    new_node->next = start;
}

/*Remove a node then returns the beginning of the list*/
bidirect_linked_list *remove_node (bidirect_linked_list *node) {
    bidirect_linked_list *prev = node->prev;
    bidirect_linked_list *next = node->next;
    if (prev)
        prev->next = next;
    if (next){
        next->prev = prev;
        free(node);
        return move_to_start(next);
    }
    free(node);
    return move_to_start(prev);
}

/*Prints from the beginning to the end*/
void print_list(bidirect_linked_list *list){
    list = move_to_start(list);
    while (list)
    {
        printf("%d ", list->data);
        list = list->next;
    }
    printf("\n");    
}

/*Drop duplicates by
- moving to the start
- tracking a current node and removing the followings identical
algorithm is O(n*n)
*/
bidirect_linked_list *drop_duplicate(bidirect_linked_list *list){
    list = move_to_start(list);
    printf("***********\n");
    printf("List before drop\n");
    printf("***********\n");
    print_list(list);
    printf("***********\n");
    bidirect_linked_list *current = list;
    while (current){
        // printf("Current data : %d\n", current->data);
        bidirect_linked_list *future = current;
        while (future) {
            future = future->next;
            if (future && (future->data == current->data)) {
                bidirect_linked_list *tmp = future->next;
                remove_node(future);
                future = tmp;
            }
        }
        current = current->next;
    }
    return list;
}

void main(void) {

    srand(time(NULL));
    // We will randomly chose numbers from 0 to 50 for more readability
    int data = rand()%50;
    bidirect_linked_list *list = create_list(data);
    /*We extend the list from both sides to demonstrate the list is bidirectional*/
    for (int i = 0; i < 100; i++){
        data = rand()%50;
        append_to_end(list, data);
    }
    for (int i = 0; i < 100; i++){
        data = rand()%50;
        append_to_start(list, data);
    }
    list = drop_duplicate(list);
    printf("\nList without duplicates : \n\n");
    print_list(list);
}