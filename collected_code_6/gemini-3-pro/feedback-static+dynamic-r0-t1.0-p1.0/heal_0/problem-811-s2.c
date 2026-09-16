#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node* next;
} Node;

Node* createNode(int first, int second) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        return NULL;
    }
    newNode->data.first = first;
    newNode->data.second = second;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int first, int second) {
    if (!head) {
        return;
    }
    Node* newNode = createNode(first, second);
    if (!newNode) {
        return;
    }
    if (!*head) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void freeList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

bool areListsIdentical(const Node* list1, const Node* list2) {
    while (list1 != NULL && list2 != NULL) {
        if (list1->data.first != list2->data.first || list1->data.second != list2->data.second) {
            return false;
        }
        list1 = list1->next;
        list2 = list2->next;
    }
    return list1 == NULL && list2 == NULL;
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* list3 = NULL;

    appendNode(&list1, 1, 2);
    appendNode(&list1, 3, 4);
    appendNode(&list1, 5, 6);

    appendNode(&list2, 1, 2);
    appendNode(&list2, 3, 4);
    appendNode(&list2, 5, 6);

    appendNode(&list3, 1, 2);
    appendNode(&list3, 9, 4);
    appendNode(&list3, 5, 6);

    if (areListsIdentical(list1, list2)) {
        printf("list1 and list2 are identical\n");
    } else {
        printf("list1 and list2 are not identical\n");
    }

    if (areListsIdentical(list1, list3)) {
        printf("list1 and list3 are identical\n");
    } else {
        printf("list1 and list3 are not identical\n");
    }

    freeList(list1);
    freeList(list2);
    freeList(list3);

    return 0;
}