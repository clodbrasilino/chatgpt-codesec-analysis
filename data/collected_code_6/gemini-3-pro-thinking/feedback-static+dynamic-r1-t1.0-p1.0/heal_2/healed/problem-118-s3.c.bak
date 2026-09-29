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

        size_t len = ptr - start;
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

        strncpy(newNode->data, start, len);
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

int main(int argc, char *argv[]) {
    if (argc > 1) {
        char buffer[8192] = "";
        for (int i = 1; i < argc; i++) {
            strncat(buffer, argv[i], sizeof(buffer) - strlen(buffer) - 1);
            if (i < argc - 1) {
                strncat(buffer, " ", sizeof(buffer) - strlen(buffer) - 1);
            }
        }
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