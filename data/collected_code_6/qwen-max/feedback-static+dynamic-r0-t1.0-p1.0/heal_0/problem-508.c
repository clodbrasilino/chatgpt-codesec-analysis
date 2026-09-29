#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node *next;
} ListNode;

ListNode* createNode(int value) {
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void appendToList(ListNode **head, int value) {
    if (*head == NULL) {
        *head = createNode(value);
    } else {
        ListNode *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = createNode(value);
    }
}

bool isSameOrder(ListNode *list1, ListNode *list2) {
    while (list1 != NULL && list2 != NULL) {
        if (list1->value == list2->value) {
            list1 = list1->next;
            list2 = list2->next;
        } else {
            list2 = list2->next;
        }
    }
    return list1 == NULL;
}

int main() {
    ListNode *list1 = NULL;
    ListNode *list2 = NULL;

    appendToList(&list1, 1);
    appendToList(&list1, 3);
    appendToList(&list1, 5);

    appendToList(&list2, 0);
    appendToList(&list2, 1);
    appendToList(&list2, 2);
    appendToList(&list2, 3);
    appendToList(&list2, 4);
    appendToList(&list2, 5);

    if (isSameOrder(list1, list2)) {
        printf("Common elements are in the same order.\n");
    } else {
        printf("Common elements are not in the same order.\n");
    }

    // Free the allocated memory
    while (list1 != NULL) {
        ListNode *temp = list1;
        list1 = list1->next;
        free(temp);
    }
    while (list2 != NULL) {
        ListNode *temp = list2;
        list2 = list2->next;
        free(temp);
    }

    return 0;
}