#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

Node* appendNode(Node* head, const char* str) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return head;
    
    newNode->data = strdup(str);
    if (!newNode->data) {
        free(newNode);
        return head;
    }
    newNode->next = NULL;
    
    if (!head) {
        return newNode;
    }
    
    Node* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

void printList(Node* head) {
    if (!head) return;
    
    printf("[");
    Node* current = head;
    while (current) {
        printf("'%s'", current->data);
        if (current->next) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

void freeList(Node* head) {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}

char* readWord(void) {
    size_t capacity = 32;
    size_t length = 0;
    char* buffer = (char*)malloc(capacity);
    int c;

    if (!buffer) return NULL;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stdin)) != EOF && isspace((unsigned char)c)) {
    }

    if (c == EOF) {
        free(buffer);
        return NULL;
    }

    do {
        if (length >= capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }
            size_t new_capacity = capacity * 2;
            char* temp = (char*)realloc(buffer, new_capacity);
            if (!temp) {
                free(buffer);
                return NULL;
            }
            buffer = temp;
            capacity = new_capacity;
        }
        buffer[length++] = (char)c;
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    } while ((c = fgetc(stdin)) != EOF && !isspace((unsigned char)c));

    buffer[length] = '\0';
    return buffer;
}

int main(void) {
    Node* head = NULL;
    char* word;
    
    while ((word = readWord()) != NULL) {
        head = appendNode(head, word);
        free(word);
    }
    
    printList(head);
    freeList(head);
    
    return EXIT_SUCCESS;
}