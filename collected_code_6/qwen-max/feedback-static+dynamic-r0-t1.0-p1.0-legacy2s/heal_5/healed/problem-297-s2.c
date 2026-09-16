#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int value;
    struct _Node *next;
} Node;

typedef struct _NestedList {
    int value;
    struct _NestedList *next;
    struct _NestedList *child;
} NestedList;

Node* newNode(int value) {
    Node *node = (Node*)malloc(sizeof(Node));
    if (node == NULL) return NULL;
    node->value = value;
    node->next = NULL;
    return node;
}

void flatten(NestedList* head, Node** tail) {
    if (head == NULL) return;
    *tail = newNode(head->value);
    Node *currentTail = *tail;

    if (head->child != NULL) {
        flatten(head->child, &currentTail->next);
        while (currentTail->next != NULL) {
            currentTail = currentTail->next;
        }
    }

    if (head->next != NULL) {
        flatten(head->next, &currentTail->next);
    }
}

int main() {
    NestedList *nested = (NestedList*)calloc(1, sizeof(NestedList));
    if (nested == NULL) return 1;
    nested->value = 1;
    nested->next = (NestedList*)calloc(1, sizeof(NestedList));
    if (nested->next == NULL) { free(nested); return 1; }
    nested->next->value = 2;
    nested->next->next = (NestedList*)calloc(1, sizeof(NestedList));
    if (nested->next->next == NULL) { free(nested->next); free(nested); return 1; }
    nested->next->next->value = 3;
    nested->next->next->next = NULL;
    nested->next->child = (NestedList*)calloc(1, sizeof(NestedList));
    if (nested->next->child == NULL) { free(nested->next->next); free(nested->next); free(nested); return 1; }
    nested->next->child->value = 5;
    nested->next->child->next = (NestedList*)calloc(1, sizeof(NestedList));
    if (nested->next->child->next == NULL) { free(nested->next->child); free(nested->next->next); free(nested->next); free(nested); return 1; }
    nested->next->child->next->value = 6;
    nested->next->child->next->next = NULL;
    nested->child = (NestedList*)calloc(1, sizeof(NestedList));
    if (nested->child == NULL) { free(nested->next->child->next); free(nested->next->child); free(nested->next->next); free(nested->next); free(nested); return 1; }
    nested->child->value = 4;
    nested->child->next = NULL;
    nested->child->child = NULL;

    Node *flattenedList = NULL;
    flatten(nested, &flattenedList);

    for (Node *ptr = flattenedList; ptr != NULL; ptr = ptr->next) {
        printf("%d ", ptr->value);
    }
    printf("\n");

    Node *ptr = flattenedList;
    while (ptr != NULL) {
        Node *next = ptr->next;
        free(ptr);
        ptr = next;
    }

    NestedList *ptrNested = nested;
    while (ptrNested != NULL) {
        NestedList *next = ptrNested->next;
        if (ptrNested->child) {
            NestedList *child = ptrNested->child;
            while (child != NULL) {
                NestedList *childNext = child->next;
                free(child);
                child = childNext;
            }
        }
        free(ptrNested);
        ptrNested = next;
    }

    return 0;
}