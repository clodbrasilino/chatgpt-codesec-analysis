#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

Node* createNode(const char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->data = strdup(word);
        newNode->next = NULL;
    }
    return newNode;
}

int main(void) {
    char buffer[4096];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }
    
    Node* head = NULL;
    Node* tail = NULL;
    
    char* token = strtok(buffer, " \t\r\n");
    while (token != NULL) {
        Node* newNode = createNode(token);
        if (newNode) {
            if (head == NULL) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
        token = strtok(NULL, " \t\r\n");
    }
    
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
    
    current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    
    return 0;
}