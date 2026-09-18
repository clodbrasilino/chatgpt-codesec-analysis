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

Tuple* extract_nth_element(Node* head, int n) {
    if (head == NULL || n < 0) {
        return NULL;
    }

    Node* current = head;
    int count = 0;

    while (current != NULL) {
        if (count == n) {
            Tuple* result = (Tuple*)malloc(sizeof(Tuple));
            if (result == NULL) {
                return NULL;
            }
            result->first = current->data.first;
            result->second = current->data.second;
            return result;
        }
        count++;
        current = current->next;
    }

    return NULL;
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

int main() {
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL) return 1;
    head->data.first = 1;
    head->data.second = 2;

    head->next = (Node*)malloc(sizeof(Node));
    if (head->next == NULL) {
        free_list(head);
        return 1;
    }
    head->next->data.first = 3;
    head->next->data.second = 4;

    head->next->next = (Node*)malloc(sizeof(Node));
    if (head->next->next == NULL) {
        free_list(head);
        return 1;
    }
    head->next->next->data.first = 5;
    head->next->next->data.second = 6;
    head->next->next->next = NULL;

    Tuple* nth_tuple = extract_nth_element(head, 1);

    if (nth_tuple != NULL) {
        printf("Tuple at index 1: (%d, %d)\n", nth_tuple->first, nth_tuple->second);
        free(nth_tuple);
    } else {
        printf("Index out of bounds or memory allocation failed.\n");
    }

    free_list(head);

    return 0;
}