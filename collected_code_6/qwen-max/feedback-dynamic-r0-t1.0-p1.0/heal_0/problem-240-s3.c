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

void appendToList(ListNode **head, int value) {
    ListNode *newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    ListNode *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void replaceLastWithList(ListNode **mainList, ListNode *replacementList) {
    if (*mainList == NULL || replacementList == NULL) {
        return;
    }
    if ((*mainList)->next == NULL) {
        free(*mainList);
        *mainList = replacementList;
        return;
    }
    ListNode *current = *mainList;
    while (current->next->next != NULL) {
        current = current->next;
    }
    current->next = replacementList;
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
    appendToList(&list1, 1);
    appendToList(&list1, 2);
    appendToList(&list1, 3);

    ListNode *list2 = NULL;
    appendToList(&list2, 4);
    appendToList(&list2, 5);

    printf("Original List: ");
    printList(list1);

    replaceLastWithList(&list1, list2);

    printf("Modified List: ");
    printList(list1);

    while (list1 != NULL) {
        ListNode *temp = list1;
        list1 = list1->next;
        free(temp);
    }

    return 0;
}