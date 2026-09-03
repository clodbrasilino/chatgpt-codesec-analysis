#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_node {
    const char *data;
    struct list_node *next;
} list_node;

char *concatenate_list(const list_node *head) {
    size_t total = 0;
    size_t len;
    const list_node *node;
    char *result;
    char *dest;

    for (node = head; node != NULL; node = node->next) {
        if (node->data == NULL) {
            continue;
        }
        len = strlen(node->data);
        if (len > (size_t)-1 - total) {
            return NULL;
        }
        total += len;
    }

    result = malloc(total + 1);
    if (result == NULL) {
        return NULL;
    }

    dest = result;
    for (node = head; node != NULL; node = node->next) {
        if (node->data == NULL) {
            continue;
        }
        len = strlen(node->data);
        memcpy(dest, node->data, len);
        dest += len;
    }
    *dest = '\0';

    return result;
}

int main(void) {
    list_node node3 = { "world", NULL };
    list_node node2 = { " ", &node3 };
    list_node node1 = { "Hello", &node2 };
    char *result;

    result = concatenate_list(&node1);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result);
    free(result);

    return EXIT_SUCCESS;
}