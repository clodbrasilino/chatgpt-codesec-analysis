#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

Node* appendNode(Node* head, const char* str) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return head;
    
    newNode->data = strdup(str);
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

    while ((c = fgetc(stdin)) != EOF && isspace(c)) {
    }

    if (c == EOF) {
        free(buffer);
        return NULL;
    }

    do {
        buffer[length++] = (char)c;
        if (length + 1 >= capacity) {
            capacity *= 2;
            char* temp = (char*)realloc(buffer, capacity);
            if (!temp) {
                buffer[length] = '\0';
                return buffer;
            }
            buffer = temp;
        }
    } while ((c = fgetc(stdin)) != EOF && !isspace(c));

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