#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char **items;
    size_t length;
} Tuple;

typedef struct {
    char **items;
    size_t length;
} List;

typedef enum {
    CONVERSION_SUCCESS,
    CONVERSION_INVALID_ARGUMENT,
    CONVERSION_ALLOCATION_FAILURE
} ConversionResult;

static char *copy_string(const char *source)
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

void free_list(List *list)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < list->length; ++i) {
        free(list->items[i]);
    }

    free(list->items);
    list->items = NULL;
    list->length = 0;
}

ConversionResult tuple_to_list(const Tuple *tuple, const char *string, List *result)
{
    List temporary = {NULL, 0};
    size_t result_length;
    size_t i;

    if (result == NULL) {
        return CONVERSION_INVALID_ARGUMENT;
    }

    result->items = NULL;
    result->length = 0;

    if (tuple == NULL || string == NULL ||
        (tuple->length > 0 && tuple->items == NULL)) {
        return CONVERSION_INVALID_ARGUMENT;
    }

    if (tuple->length > SIZE_MAX / 2) {
        return CONVERSION_ALLOCATION_FAILURE;
    }

    result_length = tuple->length * 2;

    if (result_length == 0) {
        return CONVERSION_SUCCESS;
    }

    if (result_length > SIZE_MAX / sizeof(*temporary.items)) {
        return CONVERSION_ALLOCATION_FAILURE;
    }

    temporary.items = calloc(result_length, sizeof(*temporary.items));
    if (temporary.items == NULL) {
        return CONVERSION_ALLOCATION_FAILURE;
    }

    temporary.length = result_length;

    for (i = 0; i < tuple->length; ++i) {
        if (tuple->items[i] == NULL) {
            free_list(&temporary);
            return CONVERSION_INVALID_ARGUMENT;
        }

        temporary.items[i * 2] = copy_string(tuple->items[i]);
        if (temporary.items[i * 2] == NULL) {
            free_list(&temporary);
            return CONVERSION_ALLOCATION_FAILURE;
        }

        temporary.items[i * 2 + 1] = copy_string(string);
        if (temporary.items[i * 2 + 1] == NULL) {
            free_list(&temporary);
            return CONVERSION_ALLOCATION_FAILURE;
        }
    }

    *result = temporary;
    return CONVERSION_SUCCESS;
}

int main(int argc, char *argv[])
{
    Tuple tuple;
    List list = {NULL, 0};
    ConversionResult conversion_result;
    size_t i;
    int exit_status = EXIT_SUCCESS;

    if (argc < 3) {
        if (fprintf(stderr, "Usage: %s string element [element ...]\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    tuple.items = &argv[2];
    tuple.length = (size_t)(argc - 2);

    conversion_result = tuple_to_list(&tuple, argv[1], &list);
    if (conversion_result != CONVERSION_SUCCESS) {
        if (fprintf(stderr, "Failed to convert tuple to list\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (i = 0; i < list.length; ++i) {
        if (puts(list.items[i]) == EOF) {
            exit_status = EXIT_FAILURE;
            break;
        }
    }

    free_list(&list);
    return exit_status;
}