#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

void addNode(List *list, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = list->head;
    list->head = new_node;
}

int findInList(List *list, int value) {
    Node *current = list->head;
    while (current != NULL) {
        if (current->value == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void findNestedElements(List *nested, List *elements, List *result) {
    Node *current = nested->head;
    while (current != NULL) {
        if (findInList(elements, current->value)) {
            addNode(result, current->value);
        }
        current = current->next;
    }
}

void printList(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void freeList(List *list) {
    Node *current = list->head;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    List nested;
    List elements;
    List result;
    nested.head = NULL;
    elements.head = NULL;
    result.head = NULL;

    addNode(&nested, 3);
    addNode(&nested, 2);
    addNode(&nested, 1);

    addNode(&elements, 4);
    addNode(&elements, 3);
    addNode(&elements, 1);

    findNestedElements(&nested, &elements, &result);

    printList(&result);

    freeList(&nested);
    freeList(&elements);
    freeList(&result);

    return 0;
}