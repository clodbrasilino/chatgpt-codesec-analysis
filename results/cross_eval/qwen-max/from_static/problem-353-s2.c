#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int value;
    struct List *next;
} List;

typedef struct NestedList {
    List *head;
    struct NestedList *next;
} NestedList;

NestedList* createNestedList() {
    return (NestedList*)malloc(sizeof(NestedList));
}

List* createList(int value) {
    List *new = (List*)malloc(sizeof(List));
    new->value = value;
    new->next = NULL;
    return new;
}

void appendToNestedList(NestedList *nested, List *newItem) {
    if (nested->head == NULL) {
        nested->head = newItem;
    } else {
        List *current = nested->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newItem;
    }
}

void removeColumn(NestedList *head, int index) {
    NestedList *current = head;
    while (current != NULL) {
        List *listCurrent = current->head;
        List *prev = NULL;
        int count = 0;
        while (listCurrent != NULL) {
            if (count == index) {
                if (prev == NULL) {
                    current->head = listCurrent->next;
                } else {
                    prev->next = listCurrent->next;
                }
                free(listCurrent);
                break;
            }
            prev = listCurrent;
            listCurrent = listCurrent->next;
            ++count;
        }
        current = current->next;
    }
}

void printNestedList(NestedList *head) {
    NestedList *current = head;
    while (current != NULL) {
        List *listCurrent = current->head;
        while (listCurrent != NULL) {
            printf("%d ", listCurrent->value);
            listCurrent = listCurrent->next;
        }
        printf("\n");
        current = current->next;
    }
}

int main() {
    NestedList *root = createNestedList();
    root->next = createNestedList();
    root->next->next = createNestedList();

    appendToNestedList(root, createList(1));
    appendToNestedList(root, createList(2));
    appendToNestedList(root, createList(3));

    appendToNestedList(root->next, createList(4));
    appendToNestedList(root->next, createList(5));
    appendToNestedList(root->next, createList(6));

    appendToNestedList(root->next->next, createList(7));
    appendToNestedList(root->next->next, createList(8));
    appendToNestedList(root->next->next, createList(9));

    printf("Before removing column:\n");
    printNestedList(root);

    removeColumn(root, 1);

    printf("After removing column 1:\n");
    printNestedList(root);

    return 0;
}