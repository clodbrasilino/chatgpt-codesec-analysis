#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    size_t count;
    char **items;
} StringTuple;

static void string_tuple_destroy(StringTuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    for (size_t i = 0; i < tuple->count; ++i) {
        free(tuple->items[i]);
    }

    free(tuple->items);
    free(tuple);
}

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, source, length + 1);
    return copy;
}

static StringTuple *string_list_to_tuple(const char *const list[], size_t count)
{
    StringTuple *tuple;

    if (count > 0 && list == NULL) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    tuple = malloc(sizeof(*tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->count = 0;
    tuple->items = NULL;

    if (count > 0) {
        tuple->items = calloc(count, sizeof(*tuple->items));
        if (tuple->items == NULL) {
            free(tuple);
            return NULL;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        tuple->items[i] = duplicate_string(list[i]);
        if (tuple->items[i] == NULL) {
            string_tuple_destroy(tuple);
            return NULL;
        }
        tuple->count++;
    }

    return tuple;
}

static int print_tuple(const StringTuple *tuple)
{
    if (tuple == NULL || fputc('(', stdout) == EOF) {
        return -1;
    }

    for (size_t i = 0; i < tuple->count; ++i) {
        if (i > 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (fprintf(stdout, "\"%s\"", tuple->items[i]) < 0) {
            return -1;
        }
    }

    if (tuple->count == 1 && fputc(',', stdout) == EOF) {
        return -1;
    }

    if (fputs(")\n", stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const char *string_list[] = {
        "apple",
        "banana",
        "cherry"
    };
    const size_t count = sizeof(string_list) / sizeof(string_list[0]);
    StringTuple *tuple = string_list_to_tuple(string_list, count);

    if (tuple == NULL) {
        fputs("Failed to create tuple.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_tuple(tuple) != 0) {
        fputs("Failed to print tuple.\n", stderr);
        string_tuple_destroy(tuple);
        return EXIT_FAILURE;
    }

    string_tuple_destroy(tuple);
    return EXIT_SUCCESS;
}