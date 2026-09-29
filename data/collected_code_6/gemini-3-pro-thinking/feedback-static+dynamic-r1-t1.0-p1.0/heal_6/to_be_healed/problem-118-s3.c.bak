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
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  */

Node* stringToList(const char* str) {
    Node* head = NULL;
    Node* tail = NULL;
    const char* ptr = str;

    if (str == NULL) {
        return NULL;
    }

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
    const Node* current = head;
    printf("[");
    while (current != NULL) {
        printf("'%s'", current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

int main(int argc, const char *argv[]) {
    if (argc > 1) {
        char buffer[8192];
        size_t current_len = 0;
        
        memset(buffer, 0, sizeof(buffer));
        for (int i = 1; i < argc; i++) {
            size_t arg_len = strlen(argv[i]);
            if (current_len + arg_len + 1 >= sizeof(buffer)) {
                break;
            }
            memcpy(buffer + current_len, argv[i], arg_len);
            current_len += arg_len;
            if (i < argc - 1) {
                buffer[current_len++] = ' ';
            }
        }
        buffer[current_len] = '\0';
        
        Node* listHead = stringToList(buffer);
        printList(listHead);
        freeList(listHead);
        fflush(stdout);
    } else {
        char buffer[8192];
        while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            Node* listHead = stringToList(buffer);
            printList(listHead);
            freeList(listHead);
            fflush(stdout);
        }
    }
    return EXIT_SUCCESS;
}