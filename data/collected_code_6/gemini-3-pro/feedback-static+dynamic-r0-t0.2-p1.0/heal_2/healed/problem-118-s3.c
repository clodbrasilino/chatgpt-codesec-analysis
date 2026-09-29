#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

Node* stringToList(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    Node* head = NULL;
    Node* tail = NULL;
    const char* p = str;

    while (*p) {
        while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') {
            p++;
        }
        if (*p == '\0') {
            break;
        }
        const char* start = p;
        while (*p && *p != ' ' && *p != '\t' && *p != '\n' && *p != '\r') {
            p++;
        }
        
        size_t len = p - start;
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            Node* current = head;
            while (current != NULL) {
                Node* temp = current;
                current = current->next;
                free(temp->data);
                free(temp);
            }
            return NULL;
        }

        newNode->data = (char*)malloc(len + 1);
        if (newNode->data == NULL) {
            free(newNode);
            Node* current = head;
            while (current != NULL) {
                Node* temp = current;
                current = current->next;
                free(temp->data);
                free(temp);
            }
            return NULL;
        }

        memcpy(newNode->data, start, len);
        newNode->data[len] = '\0';
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

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
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

int main(void) {
    char *input = NULL;
    size_t size = 0;
    size_t len = 0;
    int c;

    while ((c = getchar()) != EOF && c != '\n') {
        if (c == '\r') {
            continue;
        }
        if (len + 1 >= size) {
            size = (size == 0) ? 128 : size * 2;
            char *new_input = realloc(input, size);
            if (!new_input) {
                free(input);
                return EXIT_FAILURE;
            }
            input = new_input;
        }
        input[len++] = (char)c;
    }
    
    if (input == NULL && c == EOF) {
        return EXIT_SUCCESS;
    }
    
    if (input != NULL) {
        input[len] = '\0';
    } else {
        input = calloc(1, 1);
        if (!input) {
            return EXIT_FAILURE;
        }
    }

    Node* list = stringToList(input);
    
    printList(list);
    freeList(list);
    free(input);

    return EXIT_SUCCESS;
}