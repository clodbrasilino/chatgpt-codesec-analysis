#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int value;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node* next;
} Node;

int extract_rear(Node** head, Tuple* result) {
    if (head == NULL || *head == NULL || result == NULL) {
        return 0;
    }

    Node* current = *head;
    Node* previous = NULL;

    if (current->next == NULL) {
        *result = current->data;
        free(current);
        *head = NULL;
        return 1;
    }

    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }

    *result = current->data;
    free(current);
    previous->next = NULL;

    return 1;
}

void append(Node** head, Tuple data) {
    if (head == NULL) {
        return;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return;
    }

    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = new_node;
}

void free_list(Node* head) {
    Node* current = head;
    Node* next_node = NULL;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

int main() {
    Node* head = NULL;
    Tuple t1 = {1, 100};
    Tuple t2 = {2, 200};
    Tuple t3 = {3, 300};

    append(&head, t1);
    append(&head, t2);
    append(&head, t3);

    Tuple extracted;
    if (extract_rear(&head, &extracted)) {
        printf("Extracted: id=%d, value=%d\n", extracted.id, extracted.value);
    }

    free_list(head);

    return 0;
}