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

    size_t offset = 0;
    current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            size_t len = strnlen(current->data, total_length - offset);
            if (offset + len <= total_length) {
                if (total_length - offset < len) {
                    free(result);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + offset, current->data, len);
                offset += len;
            }
        }
        current = current->next;
    }
    result[offset] = '\0';

    return result;
}

int main(void) {
    Node node3 = {"world", NULL};
    Node node2 = {" ", &node3};
    Node node1 = {"Hello", &node2};

    char *result = concatenate_list(&node1);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("%s\n", result);
    free(result);

    Node *empty_list = NULL;
    char *empty_result = concatenate_list(empty_list);
    if (empty_result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Empty: '%s'\n", empty_result);
    free(empty_result);

    return 0;
}