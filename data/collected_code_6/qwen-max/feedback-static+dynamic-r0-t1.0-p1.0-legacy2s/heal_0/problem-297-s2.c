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
    // Example usage
    NestedList *nested = (NestedList*)malloc(sizeof(NestedList));
    nested->value = 1;
    nested->next = (NestedList*)malloc(sizeof(NestedList));
    nested->next->value = 2;
    nested->next->next = (NestedList*)malloc(sizeof(NestedList));
    nested->next->next->value = 3;
    nested->next->next->next = NULL;
    nested->next->child = (NestedList*)malloc(sizeof(NestedList));
    nested->next->child->value = 5;
    nested->next->child->next = (NestedList*)malloc(sizeof(NestedList));
    nested->next->child->next->value = 6;
    nested->next->child->next->next = NULL;
    nested->child = (NestedList*)malloc(sizeof(NestedList));
    nested->child->value = 4;
    nested->child->next = NULL;
    nested->child->child = NULL;
    
    Node *flattenedList = NULL;
    flatten(nested, &flattenedList);
    
    for (Node *ptr = flattenedList; ptr != NULL; ptr = ptr->next) {
        printf("%d ", ptr->value);
    }
    printf("\n");
    
    // Free the allocated memory
    Node *ptr = flattenedList;
    while (ptr != NULL) {
        Node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
    
    ptr = nested;
    while (ptr != NULL) {
        NestedList *next = ptr->next;
        if (ptr->child) {
            NestedList *child = ptr->child;
            while (child != NULL) {
                NestedList *childNext = child->next;
                free(child);
                child = childNext;
            }
        }
        free(ptr);
        ptr = next;
    }
    
    return 0;
}