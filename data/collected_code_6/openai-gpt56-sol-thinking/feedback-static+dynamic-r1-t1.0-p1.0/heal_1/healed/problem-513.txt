#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

typedef struct {
    char **items;
    size_t count;
} StringList;

static char *duplicate_string(const char *string, size_t length)
{
    char *copy;
    size_t i;

    if (string == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = string[i];
    }

    copy[length] = '\0';
    return copy;
}

static void free_list(StringList *list)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    if (list->items != NULL) {
        for (i = 0; i < list->count; ++i) {
            free(list->items[i]);
        }

        free(list->items);
    }

    list->items = NULL;
    list->count = 0;
}

static int tuple_to_list(const StringView tuple[], size_t tuple_count,
                         StringView string, StringList *output)
{
    StringList result = {NULL, 0};
    size_t count;
    size_t i;

    if (output == NULL) {
        return -1;
    }

    output->items = NULL;
    output->count = 0;

    if (string.data == NULL ||
        (tuple_count != 0 && tuple == NULL)) {
        return -1;
    }

    for (i = 0; i < tuple_count; ++i) {
        if (tuple[i].data == NULL) {
            return -1;
        }
    }

    if (tuple_count > SIZE_MAX / 2) {
        return -1;
    }

    count = tuple_count * 2;

    if (count > SIZE_MAX / sizeof(*result.items)) {
        return -1;
    }

    if (count != 0) {
        result.items = calloc(count, sizeof(*result.items));
        if (result.items == NULL) {
            return -1;
        }
    }

    result.count = count;

    for (i = 0; i < tuple_count; ++i) {
        result.items[i * 2] =
            duplicate_string(tuple[i].data, tuple[i].length);
        if (result.items[i * 2] == NULL) {
            free_list(&result);
            return -1;
        }

        result.items[i * 2 + 1] =
            duplicate_string(string.data, string.length);
        if (result.items[i * 2 + 1] == NULL) {
            free_list(&result);
            return -1;
        }
    }

    *output = result;
    return 0;
}

static int print_list(const StringList *list)
{
    size_t i;

    if (list == NULL ||
        (list->count != 0 && list->items == NULL)) {
        return -1;
    }

    if (fputc('[', stdout) == EOF) {
        return -1;
    }

    for (i = 0; i < list->count; ++i) {
        if (list->items[i] == NULL) {
            return -1;
        }

        if (i != 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (fputs(list->items[i], stdout) == EOF) {
            return -1;
        }
    }

    if (fputs("]\n", stdout) == EOF) {
        return -1;
    }

    if (fflush(stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const StringView tuple[] = {
        {"alpha", sizeof("alpha") - 1},
        {"beta", sizeof("beta") - 1},
        {"gamma", sizeof("gamma") - 1}
    };
    const StringView string = {
        "added", sizeof("added") - 1
    };
    StringList list = {NULL, 0};

    if (tuple_to_list(tuple,
                      sizeof(tuple) / sizeof(tuple[0]),
                      string,
                      &list) != 0) {
        fputs("Failed to convert tuple to list\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_list(&list) != 0) {
        free_list(&list);
        return EXIT_FAILURE;
    }

    free_list(&list);
    return EXIT_SUCCESS;
}