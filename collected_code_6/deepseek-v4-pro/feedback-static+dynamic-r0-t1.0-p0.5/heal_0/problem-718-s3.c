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

Node *create_alternate_list(Node *source) {
    if (source == NULL) {
        return NULL;
    }
    
    Node *result = NULL;
    Node *current = source;
    int take = 1;
    
    while (current != NULL) {
        if (take) {
            append_node(&result, current->data);
        }
        take = !take;
        current = current->next;
    }
    
    return result;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
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
    Node *original = NULL;
    Node *alternate = NULL;
    
    append_node(&original, 1);
    append_node(&original, 2);
    append_node(&original, 3);
    append_node(&original, 4);
    append_node(&original, 5);
    append_node(&original, 6);
    append_node(&original, 7);
    
    printf("Original list: ");
    print_list(original);
    
    alternate = create_alternate_list(original);
    
    printf("Alternate list: ");
    print_list(alternate);
    
    free_list(original);
    free_list(alternate);
    
    return 0;
}