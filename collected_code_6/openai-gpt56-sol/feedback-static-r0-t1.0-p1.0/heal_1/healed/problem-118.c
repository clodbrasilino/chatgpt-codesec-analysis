#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StringList {
    char **items;
    size_t count;
} StringList;

static void string_list_init(StringList *list)
{
    if (list != NULL) {
        list->items = NULL;
        list->count = 0;
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

static int string_list_append(StringList *list, const char *start, size_t length)
{
    if (list == NULL || start == NULL || length > SIZE_MAX - 1) {
        return -1;
    }

    if (list->count >= SIZE_MAX / sizeof(*list->items)) {
        return -1;
    }

    size_t item_size = length + 1;
    char *item = malloc(item_size);
    if (item == NULL) {
        return -1;
    }

    if (length > 0) {
        memcpy(item, start, length);
    }
    item[length] = '\0';

    size_t new_count = list->count + 1;
    char **new_items = realloc(list->items,
                               new_count * sizeof(*new_items));
    if (new_items == NULL) {
        free(item);
        return -1;
    }

    list->items = new_items;
    list->items[list->count] = item;
    list->count = new_count;

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
    if (argc != 3 || argv[1] == NULL || argv[2] == NULL ||
        argv[2][0] == '\0' || argv[2][1] != '\0') {
        const char *program = argc > 0 && argv[0] != NULL
                                  ? argv[0]
                                  : "program";
        fprintf(stderr, "Usage: %s <string> <delimiter>\n", program);
        return EXIT_FAILURE;
    }

    StringList list;
    string_list_init(&list);

    if (string_to_list(argv[1], argv[2][0], &list) != 0) {
        fputs("Failed to convert string to list\n", stderr);
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