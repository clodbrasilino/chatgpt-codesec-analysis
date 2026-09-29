#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *n = malloc(sizeof(Node));
    if (n == NULL) {
        exit(EXIT_FAILURE);
    }
    n->data = data;
    n->next = NULL;
    return n;
}

void swap_first_last(Node **head) {
    if (head == NULL || *head == NULL || (*head)->next == NULL) {
        return;
    }
    Node *first = *head;
    /* Possible weaknesses found:
     *  Assignment 'prev_last=NULL', assigned value is 0
     */
    Node *prev_last = NULL;
    Node *last = *head;
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    while (last->next != NULL) {
        prev_last = last;
        last = last->next;
    }
    last->next = first->next;
    /* Possible weaknesses found:
     *  Possible null pointer dereference: prev_last [nullPointer]
     *  Null pointer dereference
     */
    prev_last->next = first;
    first->next = NULL;
    *head = last;
}

void print_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void free_list(Node *head) {
    Node *curr = head;
    Node *next_node;
    while (curr != NULL) {
        next_node = curr->next;
        free(curr);
        curr = next_node;
    }
}

int main(void) {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);
    
    print_list(head);
    swap_first_last(&head);
    print_list(head);
    
    free_list(head);
    
    return 0;
}