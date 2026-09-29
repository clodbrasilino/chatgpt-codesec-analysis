#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

char *concatenate_list(Node *head) {
    if (head == NULL) {
        char *empty = (char *)malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t total_length = 0;
    Node *current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            size_t len = strnlen(current->data, SIZE_MAX);
            if (total_length > SIZE_MAX - len) {
                return NULL;
            }
            total_length += len;
        }
        current = current->next;
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    size_t offset = 0;
    current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            size_t len = strnlen(current->data, SIZE_MAX);
            if (len > total_length) {
                free(result);
                return NULL;
            }
            if (offset > total_length - len) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, current->data, len);
            offset += len;
        }
        current = current->next;
    }
    result[offset] = '\0';

    return result;
}

Node *create_node(const char *str) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    if (str != NULL) {
        size_t len = strnlen(str, SIZE_MAX);
        if (len >= SIZE_MAX) {
            free(node);
            return NULL;
        }
        node->data = (char *)malloc(len + 1);
        if (node->data == NULL) {
            free(node);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(node->data, str, len);
        node->data[len] = '\0';
    } else {
        node->data = NULL;
    }
    node->next = NULL;
    return node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

int main(void) {
    Node *head = create_node("Hello");
    if (head == NULL) {
        return 1;
    }
    head->next = create_node(" ");
    if (head->next == NULL) {
        free_list(head);
        return 1;
    }
    head->next->next = create_node("World");
    if (head->next->next == NULL) {
        free_list(head);
        return 1;
    }
    head->next->next->next = create_node("!");
    if (head->next->next->next == NULL) {
        free_list(head);
        return 1;
    }

    char *result = concatenate_list(head);
    if (result == NULL) {
        free_list(head);
        return 1;
    }

    printf("%s\n", result);
    free(result);
    free_list(head);
    return 0;
}