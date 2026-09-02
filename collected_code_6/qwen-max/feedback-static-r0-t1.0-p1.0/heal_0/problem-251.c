#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

ListNode* createNode(int value) {
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void insertBeforeEachElement(ListNode **head) {
    if (*head == NULL) {
        return;
    }

    ListNode *current = *head;
    while (current != NULL) {
        ListNode *newNode = createNode(current->value - 1);
        newNode->next = current;
        if (current == *head) {
            *head = newNode;
        } else {
            ListNode *prev = *head;
            while (prev->next != current) {
                prev = prev->next;
            }
            prev->next = newNode;
        }
        current = current->next;
    }
}

void printList(ListNode *head) {
    while (head != NULL) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    ListNode *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);

    printf("Original list: ");
    printList(head);

    insertBeforeEachElement(&head);

    printf("List after insertion: ");
    printList(head);

    // Free the list
    while (head != NULL) {
        ListNode *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}