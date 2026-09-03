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

void addNode(ListNode **head, int value) {
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

void removeElements(ListNode **list, ListNode *toRemove) {
    ListNode *current = *list;
    ListNode *prev = NULL;

    while (current != NULL) {
        ListNode *runner = toRemove;
        int found = 0;

        while (runner != NULL) {
            if (runner->value == current->value) {
                found = 1;
                break;
            }
            runner = runner->next;
        }

        if (found) {
            if (prev == NULL) {
                *list = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            current = prev ? prev->next : *list;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void printList(ListNode *head) {
    ListNode *current = head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    ListNode *list1 = NULL;
    addNode(&list1, 1);
    addNode(&list1, 2);
    addNode(&list1, 3);
    addNode(&list1, 4);

    ListNode *list2 = NULL;
    addNode(&list2, 2);
    addNode(&list2, 3);

    printf("Original list: ");
    printList(list1);

    removeElements(&list1, list2);

    printf("Filtered list: ");
    printList(list1);

    // Free remaining nodes in list1
    while (list1 != NULL) {
        ListNode *temp = list1;
        list1 = list1->next;
        free(temp);
    }

    // Free nodes in list2
    while (list2 != NULL) {
        ListNode *temp = list2;
        list2 = list2->next;
        free(temp);
    }

    return 0;
}