#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

Node* interleaveLists(Node* list1, Node* list2) {
    Node* result = NULL;
    Node** lastPtrRef = &result;

    while (list1 != NULL || list2 != NULL) {
        if (list1 != NULL) {
            *lastPtrRef = list1;
            lastPtrRef = &(list1->next);
            list1 = list1->next;
        }
        if (list2 != NULL) {
            *lastPtrRef = list2;
            lastPtrRef = &(list2->next);
            list2 = list2->next;
        }
    }
    return result;
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    Node* list1 = newNode(1);
    list1->next = newNode(3);
    list1->next->next = newNode(5);

    Node* list2 = newNode(2);
    list2->next = newNode(4);
    list2->next->next = newNode(6);

    Node* result = interleaveLists(list1, list2);

    printList(result);

    return 0;
}