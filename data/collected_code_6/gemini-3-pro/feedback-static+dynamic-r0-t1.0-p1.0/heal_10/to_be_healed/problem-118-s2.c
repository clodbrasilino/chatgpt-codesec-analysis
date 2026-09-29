#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  */

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
        
        size_t token_len = 0;
        while (token[token_len] != '\0') {
            token_len++;
        }
        
        newNode->data = (char*)malloc(token_len + 1);
        if (newNode->data != NULL) {
            for (size_t i = 0; i <= token_len; i++) {
                newNode->data[i] = token[i];
            }
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
    size_t capacity = 1024;
    size_t length = 0;
    char* buffer = (char*)malloc(capacity);
    
    if (buffer == NULL) {
        return 1;
    }

    int ch;
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        if (ch == '\n') {
            break;
        }
        if (length + 1 >= capacity) {
            capacity *= 2;
            char* temp = (char*)realloc(buffer, capacity);
            if (temp == NULL) {
                free(buffer);
                return 1;
            }
            buffer = temp;
        }
        buffer[length++] = (char)ch;
    }
    buffer[length] = '\0';

    if (length == 0 && ch == EOF) {
        free(buffer);
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