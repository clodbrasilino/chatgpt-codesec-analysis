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

int extract_rear_element(Node* head, int* result) {
    if (head == NULL || result == NULL) {
        return -1;
    }

    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    *result = current->data.second;
    return 0;
}

void free_list(Node* head) {
    Node* current = head;
    Node* next_node;

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

int main(void) {
    Node* head = malloc(sizeof(Node));
    if (head == NULL) {
        return 1;
    }
    head->data.first = 1;
    head->data.second = 10;

    head->next = malloc(sizeof(Node));
    if (head->next == NULL) {
        free_list(head);
        return 1;
    }
    head->next->data.first = 2;
    head->next->data.second = 20;

    head->next->next = malloc(sizeof(Node));
    if (head->next->next == NULL) {
        free_list(head);
        return 1;
    }
    head->next->next->data.first = 3;
    head->next->next->data.second = 30;
    head->next->next->next = NULL;

    int rear_element;
    if (extract_rear_element(head, &rear_element) == 0) {
        printf("%d\n", rear_element);
    } else {
        printf("Failed to extract rear element.\n");
    }

    free_list(head);

    return 0;
}