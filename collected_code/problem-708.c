#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

Node* push(Node* head, char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = head;
    return newNode;
}

Node* convertStringToList(char* str) {
    Node* head = NULL;
    int len = strlen(str);
    for (int i = len - 1; i >= 0; i--) {
        head = push(head, str[i]);
    }
    return head;
}

void printList(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        printf("%c ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    char str[] = "Hello";
    Node* head = convertStringToList(str);
    printf("Converted string to list: ");
    printList(head);
    return 0;
}