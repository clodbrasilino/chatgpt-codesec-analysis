#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

ListNode* createNode(int value) {
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void freeList(ListNode *head) {
    while (head != NULL) {
        ListNode *temp = head;
        head = head->next;
        free(temp);
    }
}

int removeDuplicates(ListNode *head, int value, int count) {
    ListNode *current = head;
    ListNode *previous = NULL;
    int removed = 0;

    while (current != NULL && removed < count) {
        if (current->value == value) {
            ListNode *toRemove = current;
            current = current->next;
            if (previous == NULL) {
                head = current;
            } else {
                previous->next = current;
            }
            free(toRemove);
            removed++;
        } else {
            previous = current;
            current = current->next;
        }
    }

    return removed;
}

int main() {
    ListNode *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);
    head->next->next->next->next->next = createNode(3);

    int valueToRemove = 3;
    int countToRemove = 2;

    int removedCount = removeDuplicates(head, valueToRemove, countToRemove);

    ListNode *current = head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");

    freeList(head);

    return 0;
}