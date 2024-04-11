#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    if (!temp) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    
    temp->data = data;
    temp->next = NULL;
    return temp;
}

Node* interleaveLists(Node* list1, Node* list2) {
    if(list1 == NULL && list2 == NULL) return NULL;
    
    Node* result = NULL;
    Node** lastPtrRef = &result;

    while (list1 != NULL && list2 != NULL) {
        *lastPtrRef = newNode(list1->data);
        lastPtrRef = &((*lastPtrRef)->next);

        *lastPtrRef = newNode(list2->data);
        lastPtrRef = &((*lastPtrRef)->next);

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