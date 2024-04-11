#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    if(temp == NULL) 
        return NULL;
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void splitList(Node* head, int n, Node** front, Node** back) {
    Node* current = head;
    Node* prev = NULL;
    int count = 0;

    while (current != NULL && count < n) {
        count++;
        prev = current;
        current = current->next;
    }

    if (prev != NULL) {
        prev->next = NULL;
    }

    *front = head;
    *back = current;
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    Node* head = newNode(1);
    if (head == NULL) return 1;
    head->next = newNode(2);
    if (head->next == NULL) return 1;
    head->next->next = newNode(3);
    if (head->next->next == NULL) return 1;
    head->next->next->next = newNode(4);
    if (head->next->next->next == NULL) return 1;
    head->next->next->next->next = newNode(5);
    if (head->next->next->next->next == NULL) return 1;

    Node* front = NULL;
    Node* back = NULL;

    splitList(head, 3, &front, &back);

    printList(front);
    printList(back);

    return 0;
}