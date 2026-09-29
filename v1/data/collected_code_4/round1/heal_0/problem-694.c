#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

struct node* insertIntoLinkedList(struct node *list, int newValue) {
    if (list == NULL) {
        struct node *newNode = malloc(sizeof(struct node));
        if (newNode == NULL) {
            printf("Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        newNode->value = newValue;
        newNode->next = NULL;
        return newNode;
    }

    if (list->value != newValue) {
        list->next = insertIntoLinkedList(list->next, newValue);
    }

    return list;
}

void printLinkedList(struct node *list) {
    if (list == NULL) {
        printf("\n");
        return;
    }
    printf("%d ", list->value);
    printLinkedList(list->next);
}

void freeLinkedList(struct node *list) {
    if (list == NULL) {
        return;
    }
    freeLinkedList(list->next);
    free(list);
}

int main(void) {
    int dictionaryValues[] = {10, 25, 15, 10, 35, 30, 15, 35};
    int numValues = sizeof(dictionaryValues) / sizeof(dictionaryValues[0]);
    struct node *uniqueValuesList = NULL;

    for (int i = 0; i < numValues; i++) {
        uniqueValuesList = insertIntoLinkedList(uniqueValuesList, dictionaryValues[i]);
    }

    printf("The unique values are: ");
    printLinkedList(uniqueValuesList);

    freeLinkedList(uniqueValuesList);
    return 0;
}