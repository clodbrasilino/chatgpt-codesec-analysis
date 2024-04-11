#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

void push(struct node** head_ref, int new_data) {
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref)    = new_node;
}

int count(struct node* start, int item) {
    struct node* temp = start;
    int count = 0;
    while (temp != NULL) {
        if (temp->data == item)
           count++;
        temp = temp->next;
    }
    return count;
}

int main() {
    struct node* start = NULL;
  
    push(&start, 1);
    push(&start, 3);
    push(&start, 1);
    push(&start, 2);
    push(&start, 1);
  
    printf("count of 1 is %d", count(start, 1));
    return 0;
}