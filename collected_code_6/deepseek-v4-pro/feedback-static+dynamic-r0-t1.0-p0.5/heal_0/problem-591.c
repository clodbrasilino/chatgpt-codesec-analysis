#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, int data) {
    Node *new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void interchange_first_last(Node **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    
    Node *first = *head;
    Node *last = *head;
    Node *prev_last = NULL;
    
    while (last->next != NULL) {
        prev_last = last;
        last = last->next;
    }
    
    if (first->next == last) {
        last->next = first;
        first->next = NULL;
        *head = last;
        return;
    }
    
    last->next = first->next;
    prev_last->next = first;
    first->next = NULL;
    *head = last;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node *list = NULL;
    
    append_node(&list, 10);
    append_node(&list, 20);
    append_node(&list, 30);
    append_node(&list, 40);
    append_node(&list, 50);
    
    printf("Original list: ");
    print_list(list);
    
    interchange_first_last(&list);
    
    printf("After interchange: ");
    print_list(list);
    
    free_list(list);
    
    return 0;
}