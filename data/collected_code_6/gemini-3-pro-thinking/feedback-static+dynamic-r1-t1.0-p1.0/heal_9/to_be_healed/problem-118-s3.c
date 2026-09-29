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
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
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

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
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

    int c;
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(fp)) != EOF && c != '\n') {
        buffer[length++] = (char)c;
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

    if (c == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(int argc, const char* argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            Node* listHead = stringToList(argv[i]);
            printList(listHead);
            freeList(listHead);
        }
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