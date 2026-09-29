#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

Node* stringToList(char* str) {
    if (str == NULL) {
        return NULL;
    }

    Node* head = NULL;
    Node* tail = NULL;

    char* token = strtok(str, " \t\n\r");
    while (token != NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            Node* current = head;
            while (current != NULL) {
                Node* next = current->next;
                free(current->data);
                free(current);
                current = next;
            }
            return NULL;
        }
        
        newNode->data = strdup(token);
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        token = strtok(NULL, " \t\n\r");
    }

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
        Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

int main(void) {
    char buffer[1024];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    Node* list = stringToList(buffer);
    
    if (list != NULL) {
        printList(list);
        freeList(list);
    } else {
        printf("[]\n");
    }

    return 0;
}