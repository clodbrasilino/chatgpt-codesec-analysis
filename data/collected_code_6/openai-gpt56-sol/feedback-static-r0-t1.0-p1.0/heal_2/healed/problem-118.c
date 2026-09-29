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

    char **items = realloc(list->items, capacity * sizeof(*items));
    if (items == NULL) {
        return -1;
    }

    list->items = items;
    list->capacity = capacity;
    return 0;
}

static int string_list_append(StringList *list, const char *start, size_t length)
{
    if (list == NULL || start == NULL || length == SIZE_MAX) {
        return -1;
    }

    if (list->count == list->capacity) {
        size_t new_capacity;

        if (list->capacity == 0) {
            new_capacity = 4;
        } else {
            if (list->capacity > SIZE_MAX / 2) {
                return -1;
            }
            new_capacity = list->capacity * 2;
        }

        if (new_capacity < list->count + 1) {
            new_capacity = list->count + 1;
        }

        if (string_list_reserve(list, new_capacity) != 0) {
            return -1;
        }
    }

    char *item = malloc(length + 1);
    if (item == NULL) {
        return -1;
    }

    if (length != 0) {
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

    string_list_init(result);

    const char *start = text;
    const char *current = text;

    for (;;) {
        if (*current == delimiter || *current == '\0') {
            size_t length = (size_t)(current - start);

            if (string_list_append(result, start, length) != 0) {
                string_list_free(result);
                return -1;
            }

            if (*current == '\0') {
                return 0;
            }

            start = current + 1;
        }

        ++current;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3 || argv[0] == NULL || argv[1] == NULL ||
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