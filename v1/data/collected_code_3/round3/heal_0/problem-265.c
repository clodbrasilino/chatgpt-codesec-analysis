#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void splitList(Node* head, int n) {
    Node* temp = head;
    int count = 0;
    while (temp != NULL) {
        count++;
        if (count == n && temp->next != NULL) {
            Node* nextNode = temp->next;
            temp->next = NULL;
            temp = nextNode;
            count = 0;
        } else {
            temp = temp->next;
        }
    }
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);
    head->next->next->next->next->next = createNode(6);
    head->next->next->next->next->next->next = createNode(7);
    head->next->next->next->next->next->next->next = createNode(8);
    head->next->next->next->next->next->next->next->next = createNode(9);
    head->next->next->next->next->next->next->next->next->next = createNode(10);

    printList(head);
    splitList(head, 3);
    printList(head);

    return 0;
}