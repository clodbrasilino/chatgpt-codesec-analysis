#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int rangeCount(Node* head, int low, int high) {
    int count = 0;
    Node* current = head;

    if(head == NULL) 
        return count;

    while(current != NULL) {
        if(current->data >= low && current->data <= high) 
            count++;
        current = current->next;
    }

    return count;
}

Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if(newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(0);
    } 
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* insertEnd(Node* head, int data) {
    Node* newNode = createNode(data);

    if(head == NULL)
        head = newNode;
    else {
        Node* last = head;
        while(last->next != NULL)
            last = last->next;
        last->next = newNode;
    }

    return head;
}

int main() {
    Node* head = NULL;

    head = insertEnd(head, 10);
    head = insertEnd(head, 20);
    head = insertEnd(head, 30);
    head = insertEnd(head, 40);
    head = insertEnd(head, 50);

    int low = 15;
    int high = 45;
    int count = rangeCount(head, low, high);
    printf("Number of elements in the list within range %d to %d is: %d\n", low, high, count);

    return 0;
}