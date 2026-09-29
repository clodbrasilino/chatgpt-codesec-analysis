#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node* next;
} Node;

int extract_nth_element(Node* head, int n, Tuple* result) {
    if (head == NULL || n < 0 || result == NULL) {
        return -1;
    }

    Node* current = head;
    int count = 0;

    while (current != NULL) {
        if (count == n) {
            *result = current->data;
            return 0;
        }
        count++;
        current = current->next;
    }

    return -1; 
}

void append_node(Node** head, int first, int second) {
    if (head == NULL) {
        return;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    
    new_node->data.first = first;
    new_node->data.second = second;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node* last = *head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
}

void free_list(Node* head) {
    Node* current = head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node* head = NULL;

    append_node(&head, 1, 2);
    append_node(&head, 3, 4);
    append_node(&head, 5, 6);
    append_node(&head, 7, 8);

    Tuple result;
    int n = 2;

    if (extract_nth_element(head, n, &result) == 0) {
        printf("(%d, %d)\n", result.first, result.second);
    } else {
        printf("Out of bounds\n");
    }

    free_list(head);

    return 0;
}