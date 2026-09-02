#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
} Dictionary;

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} LinkedList;

void addValue(LinkedList* list, int value) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) exit(EXIT_FAILURE);
    newNode->value = value;
    newNode->next = list->head;
    list->head = newNode;
}

int isUnique(LinkedList* list, int value) {
    for (Node* temp = list->head; temp != NULL; temp = temp->next) {
        if (temp->value == value) return 0;
    }
    return 1;
}

void extractUniqueValues(Dictionary* dict, int size, int** uniqueValues, int* uniqueCount) {
    LinkedList list = {NULL};
    *uniqueValues = malloc(size * sizeof(int));
    if (!*uniqueValues) exit(EXIT_FAILURE);
    *uniqueCount = 0;

    for (int i = 0; i < size; ++i) {
        if (isUnique(&list, dict[i].value)) {
            (*uniqueValues)[*uniqueCount] = dict[i].value;
            (*uniqueCount)++;
            addValue(&list, dict[i].value);
        }
    }

    freeList(&list);
}

void freeList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}

int main() {
    Dictionary dict[] = {
        {10},
        {20},
        {10},
        {30},
        {20}
    };
    int size = sizeof(dict) / sizeof(dict[0]);
    int* uniqueValues;
    int uniqueCount;

    extractUniqueValues(dict, size, &uniqueValues, &uniqueCount);

    printf("Unique values: ");
    for (int i = 0; i < uniqueCount; ++i) {
        printf("%d ", uniqueValues[i]);
    }
    printf("\n");

    free(uniqueValues);

    return 0;
}