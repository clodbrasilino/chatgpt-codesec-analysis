#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
    size_t capacity;
} StringList;

static void string_list_free(StringList *list)
{
    if (list == NULL) {
        return;
    }

    for (size_t i = 0; i < list->count; ++i) {
        free(list->items[i]);
    }

    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

static int string_list_grow(StringList *list)
{
    if (list == NULL || list->count > list->capacity) {
        errno = EINVAL;
        return -1;
    }

    size_t new_capacity;

    if (list->capacity == 0) {
        new_capacity = 8;
    } else {
        if (list->capacity > SIZE_MAX / 2) {
            errno = EOVERFLOW;
            return -1;
        }

        new_capacity = list->capacity * 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*list->items)) {
        errno = EOVERFLOW;
        return -1;
    }

    char **new_items = realloc(
        list->items,
        new_capacity * sizeof(*list->items)
    );

    if (new_items == NULL) {
        return -1;
    }

    list->items = new_items;
    list->capacity = new_capacity;
    return 0;
}

static int string_list_append(StringList *list, const char *start, size_t length)
{
    if (list == NULL || start == NULL || list->count > list->capacity) {
        errno = EINVAL;
        return -1;
    }

    if (length > SIZE_MAX - 1) {
        errno = EOVERFLOW;
        return -1;
    }

    if (list->count == list->capacity && string_list_grow(list) != 0) {
        return -1;
    }

    size_t allocation_size = length + 1;
    char *item = malloc(allocation_size);

    if (item == NULL) {
        return -1;
    }

    if (length > 0) {
        memcpy(item, start, length);
    }

    item[length] = '\0';
    list->items[list->count++] = item;
    return 0;
}

static int string_to_list(const char *text, char delimiter, StringList *result)
{
    if (text == NULL || result == NULL || delimiter == '\0') {
        errno = EINVAL;
        return -1;
    }

    StringList temporary = {0};
    const char *start = text;
    const char *current = text;

    for (;;) {
        if (*current == delimiter || *current == '\0') {
            size_t length = (size_t)(current - start);

            if (string_list_append(&temporary, start, length) != 0) {
                string_list_free(&temporary);
                return -1;
            }

            if (*current == '\0') {
                break;
            }

            start = current + 1;
        }

        ++current;
    }

    *result = temporary;
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 3 || argv == NULL || argv[0] == NULL ||
        argv[1] == NULL || argv[2] == NULL ||
        argv[2][0] == '\0' || argv[2][1] != '\0') {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <string> <delimiter>\n", program);
        return EXIT_FAILURE;
    }

    StringList list = {0};

    if (string_to_list(argv[1], argv[2][0], &list) != 0) {
        int saved_errno = errno;

        fprintf(stderr,
                "Failed to convert string to list: %s\n",
                saved_errno != 0
                    ? strerror(saved_errno)
                    : "unknown error");

        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list.count; ++i) {
        if (puts(list.items[i]) == EOF) {
            string_list_free(&list);
            return EXIT_FAILURE;
        }
    }

    string_list_free(&list);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}