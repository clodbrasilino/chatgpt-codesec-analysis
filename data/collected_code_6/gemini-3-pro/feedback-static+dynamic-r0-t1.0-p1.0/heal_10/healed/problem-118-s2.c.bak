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
        
        newNode->data = (char*)malloc(strlen(token) + 1);
        if (newNode->data != NULL) {
            strcpy(newNode->data, token);
        }
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
    if (head == NULL) {
        printf("[]\n");
        return;
    }
    printf("[");
    Node* current = head;
    while (current != NULL) {
        printf("'%s'", current->data ? current->data : "");
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
        if (current->data) {
            free(current->data);
        }
        free(current);
        current = next;
    }
}

int main(void) {
    char *buffer = malloc(1);
    if (!buffer) return 1;
    buffer[0] = '\0';
    size_t size = 1;
    char temp[4096];
    
    int got_input = 0;
    while (fgets(temp, sizeof(temp), stdin) != NULL) {
        got_input = 1;
        size += strlen(temp);
        char *new_buffer = realloc(buffer, size);
        if (!new_buffer) {
            free(buffer);
            return 1;
        }
        buffer = new_buffer;
        strcat(buffer, temp);
    }

    if (got_input) {
        Node* list = stringToList(buffer);
        printList(list);
        freeList(list);
    } else {
        printf("[]\n");
    }

    free(buffer);
    return 0;
}