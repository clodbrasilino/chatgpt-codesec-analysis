#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Tuple {
    int id;
    int value;
};

struct Node {
    struct Tuple data;
    struct Node* next;
};

int findMaxValue(struct Node* head) {
    if (head == NULL) {
        return INT_MIN;
    }

    int max_val = head->data.value;
    struct Node* current = head->next;

    while (current != NULL) {
        if (current->data.value > max_val) {
            max_val = current->data.value;
        }
        current = current->next;
    }

    return max_val;
}

struct Node* createNode(int id, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data.id = id;
    newNode->data.value = value;
    newNode->next = NULL;
    return newNode;
}

void freeList(struct Node* head) {
    struct Node* current = head;
    struct Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    struct Node* head = createNode(1, 10);
    head->next = createNode(2, 45);
    head->next->next = createNode(3, 23);
    head->next->next->next = createNode(4, 89);
    head->next->next->next->next = createNode(5, 12);

    int max_value = findMaxValue(head);
    if (max_value != INT_MIN) {
        printf("Maximum value: %d\n", max_value);
    } else {
        printf("List is empty\n");
    }

    freeList(head);
    head = NULL;

    return 0;
}