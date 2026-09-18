#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int x;
    int y;
} tuple;

typedef struct node {
    struct node* next;
    tuple data;
} node;

node* add_tuple(node* head, tuple* item) {
    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = *item;
    new_node->next = head;
    return new_node;
}

int main() {
    node* head = NULL;
    tuple item = {10, 20};
    head = add_tuple(head, &item);
    if(head != NULL) {
        printf("Tuple added to the list: (%d, %d)\n", head->data.x, head->data.y);
        free(head);
    }
    return 0;
}