#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void splitList(Node* head, int n) {
    Node* temp = head;
    int count = 1;
    while (temp != NULL) {
        if (count % n == 0 && temp->next != NULL) {
            printf("\n");
        }
        printf("%d ", temp->data);
        temp = temp->next;
        count++;
    }
}

int main() {
    Node* head = newNode(1);
    head->next = newNode(2);
    head->next->next = newNode(3);
    head->next->next->next = newNode(4);
    head->next->next->next->next = newNode(5);
    head->next->next->next->next->next = newNode(6);
    head->next->next->next->next->next->next = newNode(7);
    head->next->next->next->next->next->next->next = newNode(8);
    head->next->next->next->next->next->next->next->next = newNode(9);
    head->next->next->next->next->next->next->next->next->next = newNode(10);

    int n = 3;
    splitList(head, n);

    return 0;
}