#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

Node* interleaveLists(Node* list1, Node* list2) {
    Node* result = NULL;
    Node** lastPtrRef = &result;

    while (list1 != NULL && list2 != NULL) {
        Node* newNode1 = newNode(list1->data);
        *lastPtrRef = newNode1;
        lastPtrRef = &(newNode1->next);

        Node* newNode2 = newNode(list2->data);
        *lastPtrRef = newNode2;
        lastPtrRef = &(newNode2->next);

        list1 = list1->next;
        list2 = list2->next;
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
    list1->next = newNode(2);
    list1->next->next = newNode(3);

    Node* list2 = newNode(4);
    list2->next = newNode(5);
    list2->next->next = newNode(6);

    Node* result = interleaveLists(list1, list2);

    printList(result);

    return 0;
}