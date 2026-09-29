#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void flattenList(Node* head) {
    Node* current = head;
    while(current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
}

Node* append(Node* head, Node* nodeToAppend) {
    Node* current = head;
    while(current->next != NULL) {
        current = current->next;
    }
    current->next = nodeToAppend;
    return head;
}

int main() {
    Node* head = createNode(1);
    Node* second = createNode(2);
    Node* third = createNode(3);
    Node* fourth = createNode(4);
    Node* fifth = createNode(5);

    head->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = fifth;

    flattenList(head);

    return 0;
}