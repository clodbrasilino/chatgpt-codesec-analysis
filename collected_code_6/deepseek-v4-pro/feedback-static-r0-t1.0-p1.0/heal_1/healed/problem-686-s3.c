#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int frequency;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->frequency = 1;
    newNode->next = NULL;
    return newNode;
}

void insertOrUpdate(Node** head, int data) {
    Node* current = *head;
    Node* previous = NULL;

    while (current != NULL && current->data != data) {
        previous = current;
        current = current->next;
    }

    if (current != NULL) {
        current->frequency++;
    } else {
        Node* newNode = createNode(data);
        if (previous == NULL) {
            newNode->next = *head;
            *head = newNode;
        } else {
            previous->next = newNode;
        }
    }
}

void printFrequencies(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d occurs %d times\n", current->data, current->frequency);
        current = current->next;
    }
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void findFrequency(const int arr[], int size) {
    if (arr == NULL || size <= 0) {
        fprintf(stderr, "Invalid input\n");
        return;
    }

    Node* head = NULL;

    for (int i = 0; i < size; i++) {
        insertOrUpdate(&head, arr[i]);
    }

    printFrequencies(head);
    freeList(head);
}

int main() {
    int arr[] = {1, 2, 3, 2, 1, 3, 4, 5, 4, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);

    findFrequency(arr, size);

    return 0;
}