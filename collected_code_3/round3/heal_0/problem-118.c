#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

Node* convertStringToList(char* str) {
    Node* head = NULL;
    Node* tail = NULL;

    while (*str) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = *str++;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}

void printList(Node* head) {
    while (head) {
        printf("%c ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    char str[] = "Hello, World!";
    Node* head = convertStringToList(str);
    printList(head);

    return 0;
}