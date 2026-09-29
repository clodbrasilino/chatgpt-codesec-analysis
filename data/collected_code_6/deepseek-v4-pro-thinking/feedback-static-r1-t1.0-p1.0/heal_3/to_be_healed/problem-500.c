#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_node {
    const char *data;
    size_t length;
    struct list_node *next;
} list_node;

char *concatenate_list(const list_node *head) {
    const list_node *current = NULL;
    char *result = NULL;
    char *position = NULL;
    size_t total_length = 0;

    if (head == NULL) {
        result = malloc(1);
        if (result == NULL) {
            return NULL;
        }
        result[0] = '\0';
        return result;
    }

    for (current = head; current != NULL; current = current->next) {
        size_t len = 0;

        if (current->data == NULL) {
            continue;
        }

        len = current->length;
        if (total_length > (size_t)-1 - len) {
            return NULL;
        }
        total_length += len;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    position = result;
    for (current = head; current != NULL; current = current->next) {
        size_t len = 0;

        if (current->data == NULL) {
            continue;
        }

        len = current->length;

        if (position + len > result + total_length) {
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(position, current->data, len);
        position += len;
    }

    *position = '\0';

    return result;
}

int main(void) {
    list_node node3 = { "world", 5, NULL };
    list_node node2 = { " ", 1, &node3 };
    list_node node1 = { "Hello", 5, &node2 };
    char *combined = NULL;

    combined = concatenate_list(&node1);
    if (combined == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", combined);
    free(combined);

    return EXIT_SUCCESS;
}