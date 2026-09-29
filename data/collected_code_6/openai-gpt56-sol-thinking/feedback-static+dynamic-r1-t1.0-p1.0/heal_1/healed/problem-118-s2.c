#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct StringNode {
    char *value;
    struct StringNode *next;
} StringNode;

typedef struct {
    StringNode *head;
    StringNode *tail;
    size_t size;
} StringList;

typedef enum {
    LIST_OK = 0,
    LIST_INVALID_ARGUMENT,
    LIST_ALLOCATION_FAILURE
} ListStatus;

static void string_list_destroy(StringList *list)
{
    StringNode *node;

    if (list == NULL) {
        return;
    }

    node = list->head;
    while (node != NULL) {
        StringNode *next = node->next;

        free(node->value);
        free(node);
        node = next;
    }

    free(list);
}

static ListStatus string_list_append(
    StringList *list,
    const char *value,
    size_t length)
{
    StringNode *node;
    size_t i;

    if (list == NULL || value == NULL || length == SIZE_MAX) {
        return LIST_INVALID_ARGUMENT;
    }

    if (list->size == SIZE_MAX) {
        return LIST_ALLOCATION_FAILURE;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return LIST_ALLOCATION_FAILURE;
    }

    node->value = malloc(length + 1);
    if (node->value == NULL) {
        free(node);
        return LIST_ALLOCATION_FAILURE;
    }

    for (i = 0; i < length; ++i) {
        node->value[i] = value[i];
    }

    node->value[length] = '\0';
    node->next = NULL;

    if (list->tail == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }

    list->tail = node;
    ++list->size;

    return LIST_OK;
}

static ListStatus string_to_list(
    const char *input,
    char delimiter,
    StringList **result)
{
    StringList *list;
    const char *token_start;
    const char *current;
    size_t token_length;
    ListStatus status;

    if (input == NULL || result == NULL || delimiter == '\0') {
        return LIST_INVALID_ARGUMENT;
    }

    *result = NULL;

    list = malloc(sizeof(*list));
    if (list == NULL) {
        return LIST_ALLOCATION_FAILURE;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    token_start = input;
    current = input;
    token_length = 0;

    for (;;) {
        if (*current == delimiter || *current == '\0') {
            status = string_list_append(list, token_start, token_length);
            if (status != LIST_OK) {
                string_list_destroy(list);
                return status;
            }

            if (*current == '\0') {
                break;
            }

            token_start = current + 1;
            token_length = 0;
        } else {
            if (token_length == SIZE_MAX) {
                string_list_destroy(list);
                return LIST_ALLOCATION_FAILURE;
            }

            ++token_length;
        }

        ++current;
    }

    *result = list;
    return LIST_OK;
}

static int string_list_print(const StringList *list)
{
    const StringNode *node;

    if (list == NULL) {
        return -1;
    }

    if (putchar('[') == EOF) {
        return -1;
    }

    node = list->head;
    while (node != NULL) {
        if (printf("\"%s\"", node->value) < 0) {
            return -1;
        }

        if (node->next != NULL && fputs(", ", stdout) == EOF) {
            return -1;
        }

        node = node->next;
    }

    if (puts("]") == EOF) {
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    StringList *list = NULL;
    ListStatus status;
    char delimiter = ',';

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <string> [delimiter]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc == 3) {
        if (argv[2][0] == '\0' || argv[2][1] != '\0') {
            fputs("The delimiter must be exactly one character.\n", stderr);
            return EXIT_FAILURE;
        }

        delimiter = argv[2][0];
    }

    status = string_to_list(argv[1], delimiter, &list);
    if (status != LIST_OK) {
        if (status == LIST_ALLOCATION_FAILURE) {
            fputs("Memory allocation failed.\n", stderr);
        } else {
            fputs("Invalid argument.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    if (string_list_print(list) != 0) {
        fputs("Failed to write output.\n", stderr);
        string_list_destroy(list);
        return EXIT_FAILURE;
    }

    string_list_destroy(list);
    return EXIT_SUCCESS;
}