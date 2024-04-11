#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* createList(int base, int n) {
    Node* head = NULL;
    Node* temp = NULL;
    for (int i = 0; i < n; i++) {
        if (head == NULL) {
            head = createNode(pow(base, i));
            temp = head;
        } else {
            /* Possible weaknesses found:
             *  dereference of NULL 'temp' [CWE-476] [-Wanalyzer-null-dereference]
             */
            temp->next = createNode(pow(base, i));
            temp = temp->next;
        }
    }
    return head;
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
    int base = 2;
    int n = 10;
    Node* list = createList(base, n);
    printList(list);
    return 0;
}