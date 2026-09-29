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
        if (*current == NULL) exit(EXIT_FAILURE);

        (*current)->value = head->value;
        (*current)->next = NULL;
        current = &(*current)->next;

        if (head->child) {
            NestedList* temp = head->next;
            *current = flatten(head->child);
            while (*current) {
                current = &(*current)->next;
            }
            head = temp;
        } else {
            head = head->next;
        }
    }

    return result;
}

int main() {
    NestedList* nested1 = (NestedList*)malloc(sizeof(NestedList));
    if (nested1 == NULL) exit(EXIT_FAILURE);
    nested1->value = 1;
    nested1->next = (NestedList*)malloc(sizeof(NestedList));
    if (nested1->next == NULL) exit(EXIT_FAILURE);
    nested1->next->value = 2;
    nested1->next->next = (NestedList*)malloc(sizeof(NestedList));
    if (nested1->next->next == NULL) exit(EXIT_FAILURE);
    nested1->next->next->value = 3;
    nested1->next->next->next = NULL;
    nested1->next->child = (NestedList*)malloc(sizeof(NestedList));
    if (nested1->next->child == NULL) exit(EXIT_FAILURE);
    nested1->next->child->value = 3;
    nested1->next->child->next = (NestedList*)malloc(sizeof(NestedList));
    if (nested1->next->child->next == NULL) exit(EXIT_FAILURE);
    nested1->next->child->next->value = 3;
    nested1->next->child->next->next = NULL;
    nested1->next->child->child = NULL;
    nested1->child = (NestedList*)malloc(sizeof(NestedList));
    if (nested1->child == NULL) exit(EXIT_FAILURE);
    nested1->child->value = 2;
    nested1->child->next = (NestedList*)malloc(sizeof(NestedList));
    if (nested1->child->next == NULL) exit(EXIT_FAILURE);
    nested1->child->next->value = 3;
    nested1->child->next->next = (NestedList*)malloc(sizeof(NestedList));
    if (nested1->child->next->next == NULL) exit(EXIT_FAILURE);
    nested1->child->next->next->value = 3;
    nested1->child->next->next->next = NULL;
    nested1->child->child = NULL;

    Node* flat = flatten(nested1);

    while (flat) {
        printf("%d ", flat->value);
        Node* temp = flat;
        flat = flat->next;
        free(temp);
    }

    while (nested1) {
        NestedList* temp = nested1;
        if (temp->child) {
            while (temp->child) {
                NestedList* childTemp = temp->child;
                temp->child = temp->child->next;
                free(childTemp);
            }
        }
        nested1 = nested1->next;
        free(temp);
    }

    return 0;
}