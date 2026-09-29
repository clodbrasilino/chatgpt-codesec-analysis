#include <stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed. Exiting program.\n");
        exit(0);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* removeKthNode(Node* head, int k) {
    if (head == NULL || k < 1)
        return head;

    if (k == 1) {
        Node* nextNode = head->next;
        free(head);
        return nextNode;
    }

    Node* temp = head;
    for (int i = 1; temp != NULL && i < k - 1; i++)
        temp = temp->next;

    if (temp != NULL && temp->next != NULL) {
        Node* delNode = temp->next;
        temp->next = delNode->next;
        free(delNode);
    }
    return head;
}

int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);

    int k = 2;

    head = removeKthNode(head, k);
    /* Possible weaknesses found:
     *  Potential leak of memory pointed to by 'temp' [unix.Malloc]
     */
    for (Node* temp = head; temp != NULL; temp = temp->next)
        printf("%d ", temp->data);

    return 0;
}