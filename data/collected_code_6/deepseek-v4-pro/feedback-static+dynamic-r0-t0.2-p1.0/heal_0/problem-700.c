#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

int count_in_range(Node *head, int lower, int upper) {
    int count = 0;
    Node *current = head;
    
    while (current != NULL) {
        if (current->data >= lower && current->data <= upper) {
            count++;
        }
        current = current->next;
    }
    
    return count;
}

Node *create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, int value) {
    Node *new_node = create_node(value);
    if (new_node == NULL) {
        return;
    }
    
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

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    Node *list = NULL;
    int result;
    
    append_node(&list, 5);
    append_node(&list, 12);
    append_node(&list, 3);
    append_node(&list, 8);
    append_node(&list, 15);
    append_node(&list, 7);
    append_node(&list, 10);
    
    result = count_in_range(list, 5, 10);
    printf("Elements in range [5, 10]: %d\n", result);
    
    result = count_in_range(list, 1, 4);
    printf("Elements in range [1, 4]: %d\n", result);
    
    result = count_in_range(list, 11, 20);
    printf("Elements in range [11, 20]: %d\n", result);
    
    free_list(list);
    
    return 0;
}