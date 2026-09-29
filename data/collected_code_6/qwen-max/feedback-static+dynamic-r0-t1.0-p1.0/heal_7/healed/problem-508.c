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
    while (list1 != NULL) {
        bool found = false;
        ListNode *temp2 = list2;
        while (temp2 != NULL && !found) {
            if (temp2->value == list1->value) {
                found = true;
                ListNode *t1 = list1;
                ListNode *t2 = temp2;
                while (t1 != NULL && t2 != NULL && t1->value == t2->value) {
                    t1 = t1->next;
                    t2 = t2->next;
                }
                if (t2 == NULL) {
                    list1 = t1;
                    list2 = temp2;
                }
            }
            if (!found) {
                temp2 = temp2->next;
            }
        }
        if (!found) {
            return false;
        }
        list1 = list1->next;
    }
    return list2 == NULL || (list1 == NULL && list2 == NULL);
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