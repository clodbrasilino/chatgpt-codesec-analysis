#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* nextNode = current->next;
        free(current->data);
        free(current);
        current = nextNode;
    }
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got ["python","0"
  */

Node* stringToList(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    Node* head = NULL;
    Node* tail = NULL;
    const char* ptr = str;

    while (*ptr != '\0') {
        while (isspace((unsigned char)*ptr)) {
            ptr++;
        }
        if (*ptr == '\0') {
            break;
        }

        const char* start = ptr;
        while (*ptr != '\0' && !isspace((unsigned char)*ptr)) {
            ptr++;
        }

        size_t len = (size_t)(ptr - start);
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            freeList(head);
            return NULL;
        }

        newNode->data = (char*)malloc(len + 1);
        if (newNode->data == NULL) {
            free(newNode);
            freeList(head);
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

void printList(const Node* head) {
    printf("[");
    const Node* current = head;
    while (current != NULL) {
        printf("'%s'", current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

char* readLine(FILE* fp) {
    size_t capacity = 128;
    size_t length = 0;
    char* buffer = (char*)malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }
    buffer[0] = '\0';

    while (fgets(buffer + length, (int)(capacity - length), fp) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        length += strlen(buffer + length);
        
        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
            length--;
            break;
        }
        
        if (length + 1 >= capacity) {
            capacity *= 2;
            char* newBuffer = (char*)realloc(buffer, capacity);
            if (newBuffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = newBuffer;
        }
    }

    if (length == 0) {
        free(buffer);
        return NULL;
    }

    return buffer;
}

int main(int argc, const char* argv[]) {
    if (argc > 1) {
        Node* head = NULL;
        Node* tail = NULL;
        for (int i = 1; i < argc; i++) {
            Node* listHead = stringToList(argv[i]);
            if (listHead != NULL) {
                if (head == NULL) {
                    head = listHead;
                } else {
                    tail->next = listHead;
                }
                tail = listHead;
                while (tail->next != NULL) {
                    tail = tail->next;
                }
            }
        }
        printList(head);
        freeList(head);
    } else {
        char* line;
        while ((line = readLine(stdin)) != NULL) {
            Node* listHead = stringToList(line);
            printList(listHead);
            freeList(listHead);
            free(line);
        }
    }
    
    return EXIT_SUCCESS;
}