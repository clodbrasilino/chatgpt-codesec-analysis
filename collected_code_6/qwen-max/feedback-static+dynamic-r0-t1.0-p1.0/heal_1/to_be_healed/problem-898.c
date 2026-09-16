#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node *head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

Node* extractSublist(Node *head, int count) {
    if (head == NULL || count <= 0) return NULL;
    Node *newHead = NULL, *current = head, *previous = NULL, *newCurrent;
    while (current != NULL && count > 0) {
        if (newHead == NULL) {
            newHead = current;
            newCurrent = newHead;
        } else {
            newCurrent->next = current;
            newCurrent = newCurrent->next;
        }
        previous = current;
        current = current->next;
        count--;
    }
    if (previous != NULL) previous->next = NULL;
    return newHead;
}

int main() {
    Node *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);

    Node *sublist = extractSublist(head, 3);

    for (Node *temp = sublist; temp != NULL; temp = temp->next) {
        printf("%d\n", temp->data);
    }

    freeList(head);
    freeList(sublist);

    return 0;
}