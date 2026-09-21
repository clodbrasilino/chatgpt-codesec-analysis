#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

typedef struct {
    const StringView *items;
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

static size_t c_string_length(const char *string)
{
    size_t length = 0;

    while (string[length] != '\0') {
        ++length;
    }

    return length;
}

static ConversionResult copy_string(
    const StringView *source,
    char **destination)
{
    char *copy;
    size_t i;

    if (source == NULL || destination == NULL || source->data == NULL) {
        return CONVERSION_INVALID_ARGUMENT;
    }

    *destination = NULL;

    if (source->length == SIZE_MAX) {
        return CONVERSION_ALLOCATION_FAILURE;
    }

    copy = malloc(source->length + 1);
    if (copy == NULL) {
        return CONVERSION_ALLOCATION_FAILURE;
    }

    for (i = 0; i < source->length; ++i) {
        if (source->data[i] == '\0') {
            free(copy);
            return CONVERSION_INVALID_ARGUMENT;
        }

        copy[i] = source->data[i];
    }

    copy[source->length] = '\0';
    *destination = copy;

    return CONVERSION_SUCCESS;
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

ConversionResult tuple_to_list(
    const Tuple *tuple,
    const StringView *string,
    List *result)
{
    List temporary = {NULL, 0};
    ConversionResult status;
    size_t result_length;
    size_t i;

    if (result == NULL) {
        return CONVERSION_INVALID_ARGUMENT;
    }

    result->items = NULL;
    result->length = 0;

    if (tuple == NULL || string == NULL || string->data == NULL ||
        (tuple->length != 0 && tuple->items == NULL)) {
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
        status = copy_string(&tuple->items[i], &temporary.items[i * 2]);
        if (status != CONVERSION_SUCCESS) {
            free_list(&temporary);
            return status;
        }

        status = copy_string(string, &temporary.items[i * 2 + 1]);
        if (status != CONVERSION_SUCCESS) {
            free_list(&temporary);
            return status;
        }
    }

    *result = temporary;
    return CONVERSION_SUCCESS;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    StringView repeated_string;
    StringView *tuple_items;
    Tuple tuple;
    List list = {NULL, 0};
    ConversionResult conversion_result;
    size_t tuple_length;
    size_t i;
    int exit_status = EXIT_SUCCESS;

    program_name = (argc > 0 && argv != NULL && argv[0] != NULL)
        ? argv[0]
        : "program";

    if (argc < 3 || argv == NULL) {
        if (fprintf(
                stderr,
                "Usage: %s string element [element ...]\n",
                program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (argv[1] == NULL) {
        return EXIT_FAILURE;
    }

    tuple_length = (size_t)(argc - 2);

    if (tuple_length > SIZE_MAX / sizeof(*tuple_items)) {
        return EXIT_FAILURE;
    }

    tuple_items = malloc(tuple_length * sizeof(*tuple_items));
    if (tuple_items == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < tuple_length; ++i) {
        if (argv[i + 2] == NULL) {
            free(tuple_items);
            return EXIT_FAILURE;
        }

        tuple_items[i].data = argv[i + 2];
        tuple_items[i].length = c_string_length(argv[i + 2]);
    }

    repeated_string.data = argv[1];
    repeated_string.length = c_string_length(argv[1]);

    tuple.items = tuple_items;
    tuple.length = tuple_length;

    conversion_result = tuple_to_list(&tuple, &repeated_string, &list);
    free(tuple_items);

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