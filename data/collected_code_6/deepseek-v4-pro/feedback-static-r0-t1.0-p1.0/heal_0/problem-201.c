#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

int all_elements_same(Node *head) {
    if (head == NULL) {
        return 1;
    }
    
    int first_value = head->data;
    Node *current = head->next;
    
    while (current != NULL) {
        if (current->data != first_value) {
            return 0;
        }
        current = current->next;
    }
    
    return 1;
}

Node *create_node(int value) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    Node *temp;
    
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    Node *head = NULL;
    Node *current = NULL;
    Node *new_node;
    int values[] = {5, 5, 5, 5};
    int size = sizeof(values) / sizeof(values[0]);
    int i;
    
    for (i = 0; i < size; i++) {
        new_node = create_node(values[i]);
        if (new_node == NULL) {
            free_list(head);
            return 1;
        }
        
        if (head == NULL) {
            head = new_node;
            current = head;
        } else {
            current->next = new_node;
            current = new_node;
        }
    }
    
    if (all_elements_same(head)) {
        printf("All elements are the same.\n");
    } else {
        printf("Elements are not all the same.\n");
    }
    
    free_list(head);
    
    return 0;
}