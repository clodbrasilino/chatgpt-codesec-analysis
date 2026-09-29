#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if(!node) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;

    return node;
}

Node* zipLists(Node* list1, Node* list2) {
    if(list1 == NULL) {
        return list2;
    }
    if(list2 == NULL) {
        return list1;
    }

    Node* head = NULL, **tail = &head;

    while(list1 || list2) {
        if(list1) {
            *tail = list1;
            tail = &list1->next;
            list1 = list1->next;
        }

        if(list2) {
            *tail = list2;
            tail = &list2->next;
            list2 = list2->next;
        }
    }

    return head;
}

void printList(Node* node) {
    while(node) {
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

    Node* zippedList = zipLists(list1, list2);

    printList(zippedList);

    return 0;
}