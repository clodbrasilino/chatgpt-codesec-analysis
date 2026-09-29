#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

typedef struct NestedList {
    int value;
    struct NestedList *next;
    struct NestedList *child;
} NestedList;

ListNode* flattenNestedList(NestedList *head) {
    if (!head) return NULL;

    ListNode *result = NULL, *tail = NULL;
    NestedList *stack[100];
    int top = -1;

    stack[++top] = head;

    while (top >= 0) {
        NestedList *current = stack[top--];

        ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
        newNode->value = current->value;
        newNode->next = NULL;

        if (result == NULL) {
            result = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        if (current->child) {
            if (current->next) {
                stack[++top] = current->next;
            }
            stack[++top] = current->child;
        } else if (current->next) {
            stack[++top] = current->next;
        }
    }

    return result;
}

void printList(ListNode *head) {
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

int main() {
    NestedList *head = (NestedList *)malloc(sizeof(NestedList));
    head->value = 1;
    head->next = (NestedList *)malloc(sizeof(NestedList));
    head->next->value = 2;
    head->next->next = (NestedList *)malloc(sizeof(NestedList));
    head->next->next->value = 3;
    head->next->next->next = NULL;
    head->next->next->child = (NestedList *)malloc(sizeof(NestedList));
    head->next->next->child->value = 4;
    head->next->next->child->next = (NestedList *)malloc(sizeof(NestedList));
    head->next->next->child->next->value = 5;
    head->next->next->child->next->next = (NestedList *)malloc(sizeof(NestedList));
    head->next->next->child->next->next->value = 6;
    head->next->next->child->next->next->next = NULL;
    head->next->next->child->next->next->child = (NestedList *)malloc(sizeof(NestedList));
    head->next->next->child->next->next->child->value = 7;
    head->next->next->child->next->next->child->next = NULL;
    head->next->next->child->next->next->child->child = NULL;
    head->next->next->child->next->next->child = NULL;
    head->next->next->child->next->next = NULL;
    head->next->next->child->next = NULL;
    head->next->next->child = NULL;
    head->next->next = NULL;
    head->next = NULL;
    head->child = (NestedList *)malloc(sizeof(NestedList));
    head->child->value = 8;
    head->child->next = (NestedList *)malloc(sizeof(NestedList));
    head->child->next->value = 9;
    head->child->next->next = (NestedList *)malloc(sizeof(NestedList));
    head->child->next->next->value = 10;
    head->child->next->next->next = NULL;
    head->child->next->next->child = (NestedList *)malloc(sizeof(NestedList));
    head->child->next->next->child->value = 11;
    head->child->next->next->child->next = (NestedList *)malloc(sizeof(NestedList));
    head->child->next->next->child->next->value = 12;
    head->child->next->next->child->next->next = NULL;
    head->child->next->next->child->next->child = NULL;
    head->child->next->next->child = NULL;
    head->child->next->next = NULL;
    head->child->next = NULL;
    head->child = NULL;

    ListNode *flattened = flattenNestedList(head);
    printList(flattened);

    while (flattened) {
        ListNode *temp = flattened;
        flattened = flattened->next;
        free(temp);
    }

    return 0;
}