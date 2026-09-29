#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

typedef struct {
    char *data;
    size_t length;
} StringTupleItem;

typedef struct {
    StringTupleItem *items;
    size_t count;
} StringTuple;

void string_tuple_destroy(StringTuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    if (tuple->items != NULL) {
        for (size_t i = 0; i < tuple->count; ++i) {
            free(tuple->items[i].data);
        }
    }

    free(tuple->items);
    free(tuple);
}

StringTuple *string_list_to_tuple(const StringView *list, size_t count)
{
    if (count > 0 && list == NULL) {
        return NULL;
    }

    StringTuple *tuple = malloc(sizeof(*tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = NULL;
    tuple->count = 0;

    if (count == 0) {
        return tuple;
    }

    if (count > SIZE_MAX / sizeof(*tuple->items)) {
        free(tuple);
        return NULL;
    }

    tuple->items = calloc(count, sizeof(*tuple->items));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }

    tuple->count = count;

    for (size_t i = 0; i < count; ++i) {
        if (list[i].data == NULL || list[i].length == SIZE_MAX) {
            string_tuple_destroy(tuple);
            return NULL;
        }

        tuple->items[i].data = malloc(list[i].length + 1);
        if (tuple->items[i].data == NULL) {
            string_tuple_destroy(tuple);
            return NULL;
        }

        for (size_t j = 0; j < list[i].length; ++j) {
            if (list[i].data[j] == '\0') {
                string_tuple_destroy(tuple);
                return NULL;
            }

            tuple->items[i].data[j] = list[i].data[j];
        }

        tuple->items[i].data[list[i].length] = '\0';
        tuple->items[i].length = list[i].length;
    }

    return tuple;
}

int string_tuple_print(const StringTuple *tuple)
{
    if (tuple == NULL || (tuple->count > 0 && tuple->items == NULL)) {
        return -1;
    }

    for (size_t i = 0; i < tuple->count; ++i) {
        if (tuple->items[i].data == NULL) {
            return -1;
        }
    }

    if (putchar('(') == EOF) {
        return -1;
    }

    for (size_t i = 0; i < tuple->count; ++i) {
        if (i > 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (putchar('\'') == EOF) {
            return -1;
        }

        for (size_t j = 0; j < tuple->items[i].length; ++j) {
            unsigned char character =
                (unsigned char)tuple->items[i].data[j];

            if ((character == '\\' || character == '\'') &&
                putchar('\\') == EOF) {
                return -1;
            }

            if (putchar((int)character) == EOF) {
                return -1;
            }
        }

        if (putchar('\'') == EOF) {
            return -1;
        }
    }

    if (tuple->count == 1 && putchar(',') == EOF) {
        return -1;
    }

    if (fputs(")\n", stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    static const char alpha[] = "alpha";
    static const char beta[] = "beta";
    static const char gamma[] = "gamma";

    const StringView list[] = {
        {alpha, sizeof(alpha) - 1},
        {beta, sizeof(beta) - 1},
        {gamma, sizeof(gamma) - 1}
    };
    const size_t count = sizeof(list) / sizeof(list[0]);

    StringTuple *tuple = string_list_to_tuple(list, count);
    if (tuple == NULL) {
        fputs("Failed to create tuple\n", stderr);
        return EXIT_FAILURE;
    }

    int status = EXIT_SUCCESS;

    if (string_tuple_print(tuple) != 0) {
        status = EXIT_FAILURE;
    }

    string_tuple_destroy(tuple);
    return status;
}