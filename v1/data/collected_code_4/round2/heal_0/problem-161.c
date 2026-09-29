#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if(node == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        exit(1);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

Node* removeFromList(Node* mainList, Node* removeList) {
    Node dummy;
    dummy.next = mainList;
    Node* ptr1 = &dummy;
    Node* ptr2 = removeList;

    while (ptr1->next != NULL && ptr2 != NULL) {
        if (ptr1->next->data == ptr2->data) {
            ptr1->next = ptr1->next->next;
            ptr2 = ptr2->next;
        } else {
            ptr1 = ptr1->next;
        }
    }

    return dummy.next;
}

void printList(Node* node) {
    while (node != NULL) {
        printf(" %d ", node->data);
        node = node->next;
    }
    printf("\n");
}


int main() {

    Node* mainList = newNode(5);
    mainList->next = newNode(6);
    mainList->next->next = newNode(7);
    mainList->next->next->next = newNode(8);
    mainList->next->next->next->next = newNode(9);

    Node* removeList = newNode(6);
    removeList->next = newNode(8);

    printf("List before removing elements:");
    printList(mainList);

    mainList = removeFromList(mainList, removeList);

    printf("List after removing elements:");
    printList(mainList);

    return 0;
}