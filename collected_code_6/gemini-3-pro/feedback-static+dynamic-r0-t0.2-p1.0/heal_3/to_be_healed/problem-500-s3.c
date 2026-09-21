#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

char* concatenate_list(Node *head) {
    if (head == NULL) {
        char *empty_str = malloc(1);
        if (empty_str != NULL) {
            empty_str[0] = '\0';
        }
        return empty_str;
    }

    size_t total_length = 0;
    Node *current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            total_length += strnlen(current->data, MAX_STR_LEN);
        }
        current = current->next;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char *ptr = result;
    size_t remaining = total_length + 1;
    current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            size_t len = strnlen(current->data, MAX_STR_LEN);
            if (len > remaining - 1) {
                len = remaining - 1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(ptr, current->data, len);
            ptr += len;
            remaining -= len;
        }
        current = current->next;
    }
    *ptr = '\0';

    return result;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node *node1 = malloc(sizeof(Node));
    Node *node2 = malloc(sizeof(Node));
    Node *node3 = malloc(sizeof(Node));

    if (node1 == NULL || node2 == NULL || node3 == NULL) {
        free(node1);
        free(node2);
        free(node3);
        return 1;
    }

    node1->data = "Hello, ";
    node1->next = node2;

    node2->data = "World";
    node2->next = node3;

    node3->data = "!";
    node3->next = NULL;

    char *concatenated = concatenate_list(node1);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    }

    free_list(node1);

    return 0;
}