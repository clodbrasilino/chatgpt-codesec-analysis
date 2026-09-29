#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    const char str[] = "Hello";
    Node* head = convertStringToList(str);
    printf("Converted string to list: ");
    printList(head);

    //Don't forget to free the allocated memory  
    Node *temp = NULL;
    while(head != NULL){
        temp = head;
        head=head -> next;
        free(temp);
    }

    return 0;
}