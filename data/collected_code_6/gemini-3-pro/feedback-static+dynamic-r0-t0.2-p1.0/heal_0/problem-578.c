#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node* head) {
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

Node* interleaveLists(Node* list1, Node* list2) {
    if (!list1) return list2;
    if (!list2) return list1;

    Node* head = NULL;
    Node* tail = NULL;
    Node* curr1 = list1;
    Node* curr2 = list2;

    while (curr1 != NULL && curr2 != NULL) {
        Node* newNode1 = createNode(curr1->data);
        Node* newNode2 = createNode(curr2->data);

        if (head == NULL) {
            head = newNode1;
            tail = head;
        } else {
            tail->next = newNode1;
            tail = tail->next;
        }
        
        tail->next = newNode2;
        tail = tail->next;

        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    return head;
}

void printList(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

int main(void) {
    Node* list1 = createNode(1);
    list1->next = createNode(3);
    list1->next->next = createNode(5);

    Node* list2 = createNode(2);
    list2->next = createNode(4);
    list2->next->next = createNode(6);

    Node* interleaved = interleaveLists(list1, list2);

    printList(interleaved);

    freeList(list1);
    freeList(list2);
    freeList(interleaved);

    return 0;
}