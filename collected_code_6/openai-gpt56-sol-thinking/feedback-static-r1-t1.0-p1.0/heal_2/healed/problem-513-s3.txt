#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
    size_t i;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = source[i];
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
    size_t item_count;
    size_t i;

    if ((tuple == NULL && tuple_length != 0) ||
        string_to_add.data == NULL ||
        string_to_add.length == SIZE_MAX) {
        return NULL;
    }

    if (tuple_length > SIZE_MAX / 2) {
        return NULL;
    }

    item_count = tuple_length * 2;

    if (item_count > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    list = malloc(sizeof(*list));
    if (list == NULL) {
        return NULL;
    }

    list->items = NULL;
    list->length = 0;

    if (item_count != 0) {
        list->items = malloc(item_count * sizeof(*list->items));
        if (list->items == NULL) {
            free(list);
            return NULL;
        }
    }

    for (i = 0; i < tuple_length; ++i) {
        char *tuple_copy;
        char *added_copy;

        if (tuple[i].data == NULL || tuple[i].length == SIZE_MAX) {
            free_string_list(list);
            return NULL;
        }

        tuple_copy = copy_string(tuple[i].data, tuple[i].length);
        if (tuple_copy == NULL) {
            free_string_list(list);
            return NULL;
        }

        list->items[list->length++] = tuple_copy;

        added_copy = copy_string(
            string_to_add.data,
            string_to_add.length
        );
        if (added_copy == NULL) {
            free_string_list(list);
            return NULL;
        }

        list->items[list->length++] = added_copy;
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
        { apple, sizeof(apple) - 1 },
        { banana, sizeof(banana) - 1 },
        { orange, sizeof(orange) - 1 }
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