#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} StringTuple;

void string_tuple_destroy(StringTuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }

    for (i = 0; i < tuple->count; ++i) {
        free(tuple->items[i]);
    }

    free(tuple->items);
    free(tuple);
}

StringTuple *string_list_to_tuple(const char *const *list, size_t count)
{
    StringTuple *tuple;
    size_t i;

    if (count > 0 && list == NULL) {
        return NULL;
    }

    tuple = malloc(sizeof(*tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = NULL;
    tuple->count = count;

    if (count == 0) {
        return tuple;
    }

    if (count > SIZE_MAX / sizeof(*tuple->items)) {
        string_tuple_destroy(tuple);
        return NULL;
    }

    tuple->items = calloc(count, sizeof(*tuple->items));
    if (tuple->items == NULL) {
        string_tuple_destroy(tuple);
        return NULL;
    }

    for (i = 0; i < count; ++i) {
        size_t length;

        if (list[i] == NULL) {
            string_tuple_destroy(tuple);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        length = strlen(list[i]);
        if (length == SIZE_MAX) {
            string_tuple_destroy(tuple);
            return NULL;
        }

        tuple->items[i] = malloc(length + 1);
        if (tuple->items[i] == NULL) {
            string_tuple_destroy(tuple);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tuple->items[i], list[i], length + 1);
    }

    return tuple;
}

int string_tuple_print(const StringTuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return -1;
    }

    if (putchar('(') == EOF) {
        return -1;
    }

    for (i = 0; i < tuple->count; ++i) {
        const unsigned char *text;

        if (i > 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (putchar('\'') == EOF) {
            return -1;
        }

        text = (const unsigned char *)tuple->items[i];
        while (*text != '\0') {
            if ((*text == '\\' || *text == '\'') && putchar('\\') == EOF) {
                return -1;
            }

            if (putchar((int)*text) == EOF) {
                return -1;
            }

            ++text;
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
    const char *list[] = {"alpha", "beta", "gamma"};
    const size_t count = sizeof(list) / sizeof(list[0]);
    StringTuple *tuple;
    int status = EXIT_SUCCESS;

    tuple = string_list_to_tuple(list, count);
    if (tuple == NULL) {
        fputs("Failed to create tuple\n", stderr);
        return EXIT_FAILURE;
    }

    if (string_tuple_print(tuple) != 0) {
        status = EXIT_FAILURE;
    }

    string_tuple_destroy(tuple);
    return status;
}