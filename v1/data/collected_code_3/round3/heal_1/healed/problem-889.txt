#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* reverseList(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Node* head = createNode(1);
    if (head == NULL) return 1;
    
    Node* secondNode = createNode(2);
    if (secondNode == NULL) return 1;
    head->next = secondNode;
    
    Node* thirdNode = createNode(3);
    if (thirdNode == NULL) return 1;
    secondNode->next = thirdNode;
    
    Node* fourthNode = createNode(4);
    if (fourthNode == NULL) return 1;
    thirdNode->next = fourthNode;
    
    Node* fifthNode = createNode(5);
    if (fifthNode == NULL) return 1;
    fourthNode->next = fifthNode;

    printf("Original List: \n");
    printList(head);

    head = reverseList(head);

    printf("Reversed List: \n");
    printList(head);

    return 0;
}