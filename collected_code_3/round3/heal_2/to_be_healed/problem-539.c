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
    Node* temp;

    /* Possible weaknesses found:
     *  leak of 'head' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            head = createNode(pow(base, i));
            temp = head;
        } else {
            if (temp != NULL) {
                temp->next = createNode(pow(base, i));
                temp = temp->next;
            }
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