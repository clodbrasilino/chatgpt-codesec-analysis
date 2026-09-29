#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

Node* appendNode(Node* head, const char* str) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return head;
    
    newNode->data = strdup(str);
    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    }

    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;

    return head;
}

void printList(Node* head) {
    printf("[");
    Node* current = head;
    while (current != NULL) {
        printf("'%s'", current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}

int main(void) {
    char buffer[4096];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\r\n")] = '\0';

    Node* head = NULL;
    char* token = strtok(buffer, " \t");

    while (token != NULL) {
        if (strlen(token) > 0) {
            head = appendNode(head, token);
        }
        token = strtok(NULL, " \t");
    }

    printList(head);
    freeList(head);

    return EXIT_SUCCESS;
}