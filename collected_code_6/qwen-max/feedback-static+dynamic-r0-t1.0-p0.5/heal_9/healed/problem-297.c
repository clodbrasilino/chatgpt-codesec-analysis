#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct NestedList {
    int value;
    struct NestedList *next;
    struct NestedList *child;
} NestedList;

Node* flatten(NestedList* head) {
    if (!head) return NULL;

    Node* result = NULL;
    Node** current = &result;

    while (head) {
        *current = (Node*)malloc(sizeof(Node));
        if (*current == NULL) {
            exit(1);
        }
        (*current)->value = head->value;
        (*current)->next = NULL;
        current = &(*current)->next;

        if (head->child) {
            Node* childResult = flatten(head->child);
            *current = childResult;
            while (*current) {
                current = &(*current)->next;
            }
        }

        head = head->next;
    }

    return result;
}

int main() {
    NestedList* head = (NestedList*)malloc(sizeof(NestedList));
    if (head == NULL) return 1;
    head->value = 1;
    head->next = (NestedList*)malloc(sizeof(NestedList));
    if (head->next == NULL) {
        free(head);
        return 1;
    }
    head->next->value = 2;
    head->next->next = (NestedList*)malloc(sizeof(NestedList));
    if (head->next->next == NULL) {
        free(head->next);
        free(head);
        return 1;
    }
    head->next->next->value = 3;
    head->next->next->next = NULL;
    head->next->child = (NestedList*)malloc(sizeof(NestedList));
    if (head->next->child == NULL) {
        free(head->next->next);
        free(head->next);
        free(head);
        return 1;
    }
    head->next->child->value = 4;
    head->next->child->next = (NestedList*)malloc(sizeof(NestedList));
    if (head->next->child->next == NULL) {
        free(head->next->child);
        free(head->next->next);
        free(head->next);
        free(head);
        return 1;
    }
    head->next->child->next->value = 5;
    head->next->child->next->next = (NestedList*)malloc(sizeof(NestedList));
    if (head->next->child->next->next == NULL) {
        free(head->next->child->next);
        free(head->next->child);
        free(head->next->next);
        free(head->next);
        free(head);
        return 1;
    }
    head->next->child->next->next->value = 6;
    head->next->child->next->next->next = NULL;
    head->next->child->child = NULL;
    head->child = NULL;

    Node* flatList = flatten(head);

    while (flatList) {
        printf("%d ", flatList->value);
        Node* temp = flatList;
        flatList = flatList->next;
        free(temp);
    }

    while (head) {
        NestedList* temp = head;
        head = head->next;
        if (temp->child) {
            while (temp->child) {
                NestedList* childTemp = temp->child;
                temp->child = temp->child->next;
                free(childTemp);
            }
        }
        free(temp);
    }

    return 0;
}