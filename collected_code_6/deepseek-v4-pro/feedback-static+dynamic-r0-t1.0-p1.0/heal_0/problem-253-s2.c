#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int count_integers(Node* head) {
    int count = 0;
    Node* current = head;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    return count;
}

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

int append_node(Node** head, int value) {
    Node* new_node = create_node(value);
    if (new_node == NULL) {
        return 0;
    }
    
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    
    return 1;
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node* head = NULL;
    int values[] = {10, 20, 30, 40, 50};
    size_t num_values = sizeof(values) / sizeof(values[0]);
    
    for (size_t i = 0; i < num_values; i++) {
        if (!append_node(&head, values[i])) {
            free_list(head);
            return 1;
        }
    }
    
    int total = count_integers(head);
    printf("Total integers in list: %d\n", total);
    
    free_list(head);
    return 0;
}