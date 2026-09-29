#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* interleaveLists(Node* list1, Node* list2) {
    Node* result = NULL;
    Node** lastPtrRef = &result;

    while (list1 != NULL && list2 != NULL) {
        Node* newNode1 = (Node*)malloc(sizeof(Node));
        if (!newNode1) {
            return NULL;
        }
        newNode1->data = list1->data;
        newNode1->next = NULL;
        *lastPtrRef = newNode1;
        lastPtrRef = &(newNode1->next);

        Node* newNode2 = (Node*)malloc(sizeof(Node));
        if (!newNode2) {
            return NULL;
        }
        newNode2->data = list2->data;
        newNode2->next = NULL;
        *lastPtrRef = newNode2;
        lastPtrRef = &(newNode2->next);

        list1 = list1->next;
        list2 = list2->next;
    }

    if (list1 != NULL) {
        *lastPtrRef = list1;
    } else if (list2 != NULL) {
        *lastPtrRef = list2;
    }

    return result;
}

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));

    if (!node) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;

    return node;
}

void printList(Node* node) {
    while (node) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    Node* list1 = newNode(1);
    if(list1 != NULL)
    {
        list1->next = newNode(2);
        if(list1->next != NULL)
        {
            list1->next->next = newNode(3);
        }
    }

    Node* list2 = newNode(4);
    if(list2 != NULL)
    {
        list2->next = newNode(5);
        if(list2->next != NULL)
        {
            list2->next->next = newNode(6);
        }
    }

    Node* result = interleaveLists(list1, list2);
    
    printList(result);

    return 0;
}