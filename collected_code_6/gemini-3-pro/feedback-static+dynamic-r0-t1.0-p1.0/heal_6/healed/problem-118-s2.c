#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

Node* stringToList(char* str) {
    if (str == NULL || *str == '\0') {
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
        
        size_t token_len = strlen(token);
        
        newNode->data = (char*)malloc(token_len + 1);
        if (newNode->data != NULL) {
            memcpy(newNode->data, token, token_len + 1);
        } else {
            free(newNode);
            Node* current = head;
            while (current != NULL) {
                Node* next = current->next;
                free(current->data);
                free(current);
                current = next;
            }
            return NULL;
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
    size_t capacity = 256;
    size_t length = 0;
    char* buffer = (char*)malloc(capacity);
    
    if (buffer == NULL) {
        return 1;
    }

    buffer[0] = '\0';
    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        free(buffer);
        printf("[]\n");
        return 0;
    }

    while (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        length = strlen(buffer);
        capacity *= 2;
        char* temp = (char*)realloc(buffer, capacity);
        if (temp == NULL) {
            free(buffer);
            return 1;
        }
        buffer = temp;
        if (fgets(buffer + length, (int)(capacity - length), stdin) == NULL) {
            break;
        }
    }

    length = strlen(buffer);
    if (length == 0) {
        free(buffer);
        printf("[]\n");
        return 0;
    }

    Node* list = stringToList(buffer);
    
    printList(list);
    
    if (list != NULL) {
        freeList(list);
    }

    free(buffer);
    return 0;
}