#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

typedef struct {
    char **items;
    size_t length;
} StringList;

static char *copy_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
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
    const StringView tuple[],
    size_t tuple_length,
    StringView string_to_add)
{
    StringList *list;
    size_t list_length;
    size_t i;

    if ((tuple == NULL && tuple_length != 0) ||
        string_to_add.data == NULL) {
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
        size_t first_index = i * 2;
        size_t second_index = first_index + 1;

        if (tuple[i].data == NULL) {
            free_string_list(list);
            return NULL;
        }

        list->items[first_index] =
            copy_string(tuple[i].data, tuple[i].length);
        if (list->items[first_index] == NULL) {
            free_string_list(list);
            return NULL;
        }

        list->items[second_index] =
            copy_string(string_to_add.data, string_to_add.length);
        if (list->items[second_index] == NULL) {
            free_string_list(list);
            return NULL;
        }
    }

    return list;
}

int main(void)
{
    static const char apple[] = "apple";
    static const char banana[] = "banana";
    static const char orange[] = "orange";
    static const char added[] = "added";

    const StringView tuple[] = {
        {apple, sizeof(apple) - 1},
        {banana, sizeof(banana) - 1},
        {orange, sizeof(orange) - 1}
    };
    const StringView string_to_add = {
        added,
        sizeof(added) - 1
    };
    const size_t tuple_length = sizeof(tuple) / sizeof(tuple[0]);
    StringList *list;
    size_t i;

    list = tuple_to_list(tuple, tuple_length, string_to_add);
    if (list == NULL) {
        fputs("Failed to convert tuple to list.\n", stderr);
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