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

Node* addNode(Node* head, int data) {
    Node* newNode = createNode(data);
    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    return head;
}

Node* map(Node* head, int (*f)(int, int), int base) {
    Node* temp = head;
    int index = 0;
    while (temp) {
        temp->data = f(base, index);
        temp = temp->next;
        index++;
    }
    return head;
}

int power(int base, int index) {
    return pow(base, index);
}

void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;
    for (int i = 0; i < 10; i++) {
        head = addNode(head, 0);
    }
    head = map(head, power, 2);
    printList(head);
    return 0;
}