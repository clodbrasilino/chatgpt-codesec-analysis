#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

List* createList() {
    List *list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    return list;
}

void addToList(List *list, int value) {
    Node *newNode = createNode(value);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int countSublistsContainingElement(List *list, int element) {
    int count = 0;
    Node *current = list->head;
    while (current != NULL) {
        if (current->value == element) {
            count++;
        }
        current = current->next;
    }
    return count;
}

int main() {
    List *list = createList();
    addToList(list, 1);
    addToList(list, 2);
    addToList(list, 3);
    addToList(list, 2);
    addToList(list, 4);

    int element = 2;
    int result = countSublistsContainingElement(list, element);
    printf("Number of sublists containing %d: %d\n", element, result);

    // Free allocated memory
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);

    return 0;
}