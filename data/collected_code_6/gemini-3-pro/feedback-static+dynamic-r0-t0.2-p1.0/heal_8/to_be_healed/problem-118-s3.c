#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  */

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

        for (size_t i = 0; i < len; i++) {
            newNode->data[i] = start[i];
        }
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
    size_t capacity = 1024;
    size_t len = 0;
    char *input = (char*)malloc(capacity);
    
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    int ch;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (len + 1 >= capacity) {
            capacity *= 2;
            char *temp = (char*)realloc(input, capacity);
            if (temp == NULL) {
                free(input);
                return EXIT_FAILURE;
            }
            input = temp;
        }
        input[len++] = (char)ch;
    }
    input[len] = '\0';

    Node* list = stringToList(input);
    
    printList(list);
    freeList(list);
    free(input);

    return EXIT_SUCCESS;
}