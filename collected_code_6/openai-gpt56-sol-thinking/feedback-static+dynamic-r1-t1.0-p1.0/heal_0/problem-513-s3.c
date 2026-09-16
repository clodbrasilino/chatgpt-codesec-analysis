#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t length;
} StringList;

static char *copy_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    length = strlen(source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1);
    return copy;
}

static void free_string_list(StringList *list)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < list->length; ++i) {
        free(list->items[i]);
    }

    free(list->items);
    free(list);
}

static StringList *tuple_to_list(
    const char *const tuple[],
    size_t tuple_length,
    const char *string_to_add)
{
    StringList *list;
    size_t list_length;
    size_t i;

    if ((tuple == NULL && tuple_length != 0) || string_to_add == NULL) {
        return NULL;
    }

    if (tuple_length > SIZE_MAX / 2) {
        return NULL;
    }

    list_length = tuple_length * 2;
    if (list_length > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    list = malloc(sizeof(*list));
    if (list == NULL) {
        return NULL;
    }

    list->items = NULL;
    list->length = list_length;

    if (list_length != 0) {
        list->items = calloc(list_length, sizeof(*list->items));
        if (list->items == NULL) {
            free(list);
            return NULL;
        }
    }

    for (i = 0; i < tuple_length; ++i) {
        if (tuple[i] == NULL) {
            free_string_list(list);
            return NULL;
        }

        list->items[i * 2] = copy_string(tuple[i]);
        if (list->items[i * 2] == NULL) {
            free_string_list(list);
            return NULL;
        }

        list->items[i * 2 + 1] = copy_string(string_to_add);
        if (list->items[i * 2 + 1] == NULL) {
            free_string_list(list);
            return NULL;
        }
    }

    return list;
}

int main(void)
{
    const char *const tuple[] = {"apple", "banana", "orange"};
    const size_t tuple_length = sizeof(tuple) / sizeof(tuple[0]);
    StringList *list;
    size_t i;

    list = tuple_to_list(tuple, tuple_length, "added");
    if (list == NULL) {
        if (fputs("Failed to convert tuple to list.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (i = 0; i < list->length; ++i) {
        if (puts(list->items[i]) == EOF) {
            free_string_list(list);
            return EXIT_FAILURE;
        }
    }

    free_string_list(list);
    return EXIT_SUCCESS;
}