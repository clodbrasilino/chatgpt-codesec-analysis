#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL) {
        return NULL;
    }

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
    if (head == NULL) {
        return 1;
    }

    Node* current = head;
    for (int i = 2; i <= 10; i++) {
        current->next = newNode(i);
        if (current->next == NULL) {
            return 1;
        }
        current = current->next;
    }

    int n = 3;
    splitList(head, n);

    return 0;
}