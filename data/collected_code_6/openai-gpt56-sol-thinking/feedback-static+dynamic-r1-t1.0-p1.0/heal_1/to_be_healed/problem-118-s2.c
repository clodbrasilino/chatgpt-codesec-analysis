#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    StringNode *next;

    if (list == NULL) {
        return;
    }

    node = list->head;
    while (node != NULL) {
        next = node->next;
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

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(node->value, value, length);
    node->value[length] = '\0';
    node->next = NULL;

    if (list->tail == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }

    list->tail = node;
    list->size++;

    return LIST_OK;
}

static ListStatus string_to_list(
    const char *input,
    char delimiter,
    StringList **result)
{
    StringList *list;
    const char *start;
    const char *current;
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

    start = input;
    current = input;

    for (;;) {
        if (*current == delimiter || *current == '\0') {
            status = string_list_append(
                list,
                start,
                (size_t)(current - start));

            if (status != LIST_OK) {
                string_list_destroy(list);
                return status;
            }

            if (*current == '\0') {
                break;
            }

            start = current + 1;
        }

        current++;
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
    StringList *list;
    ListStatus status;
    char delimiter;

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <string> [delimiter]\n", argv[0]);
        return EXIT_FAILURE;
    }

    delimiter = ',';

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
        string_list_destroy(list);
        return EXIT_FAILURE;
    }

    string_list_destroy(list);
    return EXIT_SUCCESS;
}