#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
    size_t capacity;
} StringList;

static void string_list_init(StringList *list)
{
    if (list != NULL) {
        list->items = NULL;
        list->count = 0;
        list->capacity = 0;
    }
}

static void string_list_free(StringList *list)
{
    if (list == NULL) {
        return;
    }

    for (size_t i = 0; i < list->count; ++i) {
        free(list->items[i]);
    }

    free(list->items);
    string_list_init(list);
}

static int string_list_reserve(StringList *list, size_t capacity)
{
    if (list == NULL) {
        return -1;
    }

    if (capacity <= list->capacity) {
        return 0;
    }

    if (capacity > SIZE_MAX / sizeof(*list->items)) {
        return -1;
    }

    char **new_items = realloc(list->items, capacity * sizeof(*new_items));
    if (new_items == NULL) {
        return -1;
    }

    list->items = new_items;
    list->capacity = capacity;
    return 0;
}

static int string_list_append(StringList *list, const char *start, size_t length)
{
    if (list == NULL || start == NULL || length == SIZE_MAX) {
        return -1;
    }

    if (list->count == SIZE_MAX) {
        return -1;
    }

    if (list->count == list->capacity) {
        size_t required = list->count + 1;
        size_t new_capacity;

        if (list->capacity == 0) {
            new_capacity = 4;
        } else if (list->capacity > SIZE_MAX / 2) {
            new_capacity = required;
        } else {
            new_capacity = list->capacity * 2;
        }

        if (new_capacity < required ||
            string_list_reserve(list, new_capacity) != 0) {
            return -1;
        }
    }

    size_t allocation_size = length + 1;
    char *item = malloc(allocation_size);
    if (item == NULL) {
        return -1;
    }

    if (length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(item, start, length);
    }
    item[length] = '\0';

    list->items[list->count++] = item;
    return 0;
}

static int string_to_list(const char *text, char delimiter, StringList *result)
{
    if (text == NULL || result == NULL || delimiter == '\0') {
        return -1;
    }

    StringList temporary;
    string_list_init(&temporary);

    const char *start = text;
    const char *current = text;

    for (;;) {
        const char character = *current;

        if (character == delimiter || character == '\0') {
            size_t length = (size_t)(current - start);

            if (string_list_append(&temporary, start, length) != 0) {
                string_list_free(&temporary);
                return -1;
            }

            if (character == '\0') {
                *result = temporary;
                return 0;
            }

            start = current + 1;
        }

        ++current;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3 || argv == NULL || argv[0] == NULL || argv[1] == NULL ||
        argv[2] == NULL || argv[2][0] == '\0' || argv[2][1] != '\0') {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <string> <delimiter>\n", program);
        return EXIT_FAILURE;
    }

    StringList list;
    string_list_init(&list);

    if (string_to_list(argv[1], argv[2][0], &list) != 0) {
        fputs("Failed to convert string to list\n", stderr);
        return EXIT_FAILURE;
    }

    int status = EXIT_SUCCESS;

    for (size_t i = 0; i < list.count; ++i) {
        if (puts(list.items[i]) == EOF) {
            status = EXIT_FAILURE;
            break;
        }
    }

    string_list_free(&list);

    if (fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    return status;
}