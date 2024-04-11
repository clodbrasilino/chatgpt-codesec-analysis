#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

Node* stringToList(char* str) {
    Node* head = NULL;
    Node* tail = NULL;

    while (*str) {
        Node* newNode = (Node*)malloc(sizeof(Node));

        if(newNode == NULL) {
            return NULL;
        }

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
    Node* list = stringToList(str);
    
    if(list == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return EXIT_FAILURE;
    }

    printList(list); 
    return EXIT_SUCCESS;
}