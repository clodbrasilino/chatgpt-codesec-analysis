#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

Node* push(Node* head, char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->next = head;
    return newNode;
}

Node* convertStringToList(const char* str) {
    Node* head = NULL;

    if(str == NULL){
        fprintf(stderr, "Input string is NULL\n");
        exit(EXIT_FAILURE);
    }

    size_t len = strnlen(str, INT_MAX);
    for (size_t i = len; i > 0; i--) {
        head = push(head, str[i-1]);
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
    const char str[] = "Hello";
    Node* head = convertStringToList(str);
    printf("Converted string to list: ");
    printList(head);

    Node *temp = NULL;
    while(head != NULL){
        temp = head;
        head = head -> next;
        free(temp);
    }

    return 0;
}