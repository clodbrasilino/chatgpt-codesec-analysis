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

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t len = strlen(str);
    
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
        head=head -> next;
        free(temp);
    }

    return 0;
}