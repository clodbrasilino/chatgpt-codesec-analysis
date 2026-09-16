#include <stdio.h>
#include <stdlib.h>

typedef struct SubListNode {
    int value;
    struct SubListNode* next;
} SubListNode;

typedef struct ListNode {
    SubListNode* head;
    int size;
    struct ListNode* next;
} ListNode;

SubListNode* createSubListNode(int value) {
    SubListNode* newNode = (SubListNode*)malloc(sizeof(SubListNode));
    if (!newNode) exit(1);
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

ListNode* createListNode() {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (!newNode) exit(1);
    newNode->head = NULL;
    newNode->size = 0;
    newNode->next = NULL;
    return newNode;
}

void appendSubListNode(ListNode* list, int value) {
    if (!list) return;
    SubListNode* newNode = createSubListNode(value);
    if (!list->head) {
        list->head = newNode;
    } else {
        SubListNode* current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

void freeSubList(SubListNode* head) {
    while (head) {
        SubListNode* temp = head;
        head = head->next;
        free(temp);
    }
}

ListNode* removeSublistsOutsideRange(ListNode* head, int minSize, int maxSize) {
    ListNode dummy;
    dummy.next = head;
    ListNode* current = &dummy;

    while (current->next) {
        if (current->next->size < minSize || current->next->size > maxSize) {
            ListNode* temp = current->next;
            current->next = temp->next;
            freeSubList(temp->head);
            free(temp);
        } else {
            current = current->next;
        }
    }
    return dummy.next;
}

void freeList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        freeSubList(temp->head);
        free(temp);
    }
}

void printList(ListNode* head) {
    while (head) {
        printf("Size %d: [", head->size);
        SubListNode* current = head->head;
        while (current) {
            printf("%d", current->value);
            if (current->next) printf(", ");
            current = current->next;
        }
        printf("]\n");
        head = head->next;
    }
}

int main(void) {
    ListNode* head = createListNode();
    appendSubListNode(head, 1);
    appendSubListNode(head, 2);

    ListNode* node2 = createListNode();
    appendSubListNode(node2, 3);

    ListNode* node3 = createListNode();
    appendSubListNode(node3, 4);
    appendSubListNode(node3, 5);
    appendSubListNode(node3, 6);
    node3->size = 3;

    head->next = node2;
    node2->next = node3;

    head = removeSublistsOutsideRange(head, 2, 2);

    printList(head);

    freeList(head);

    return 0;
}