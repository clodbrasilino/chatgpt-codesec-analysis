#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

typedef struct {
    StringView *items;
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

static size_t string_length(const char *source)
{
    size_t length = 0;

    while (source[length] != '\0') {
        ++length;
    }

    return length;
}

static ConversionResult copy_string(StringView source, char **destination)
{
    char *copy;

    if (destination == NULL || source.data == NULL) {
        return CONVERSION_INVALID_ARGUMENT;
    }

    *destination = NULL;

    if (source.length == SIZE_MAX) {
        return CONVERSION_ALLOCATION_FAILURE;
    }

    copy = malloc(source.length + 1);
    if (copy == NULL) {
        return CONVERSION_ALLOCATION_FAILURE;
    }

    for (size_t i = 0; i < source.length; ++i) {
        copy[i] = source.data[i];
    }

    copy[source.length] = '\0';
    *destination = copy;

    return CONVERSION_SUCCESS;
}

static void free_list(List *list)
{
    if (list == NULL) {
        return;
    }

    for (size_t i = 0; i < list->length; ++i) {
        free(list->items[i]);
    }

    free(list->items);
    list->items = NULL;
    list->length = 0;
}

static ConversionResult tuple_to_list(
    const Tuple *tuple,
    const StringView *string,
    List *result)
{
    List temporary = {NULL, 0};
    size_t result_length;

    if (result == NULL) {
        return CONVERSION_INVALID_ARGUMENT;
    }

    result->items = NULL;
    result->length = 0;

    if (tuple == NULL ||
        string == NULL ||
        string->data == NULL ||
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

    for (size_t i = 0; i < tuple->length; ++i) {
        size_t output_index = i * 2;
        ConversionResult status;

        if (tuple->items[i].data == NULL) {
            free_list(&temporary);
            return CONVERSION_INVALID_ARGUMENT;
        }

        status = copy_string(
            tuple->items[i],
            &temporary.items[output_index]
        );

        if (status != CONVERSION_SUCCESS) {
            free_list(&temporary);
            return status;
        }

        status = copy_string(
            *string,
            &temporary.items[output_index + 1]
        );

        if (status != CONVERSION_SUCCESS) {
            free_list(&temporary);
            return status;
        }
    }

    *result = temporary;
    return CONVERSION_SUCCESS;
}

int main(int argc, char * const argv[])
{
    Tuple tuple = {NULL, 0};
    StringView string = {NULL, 0};
    List list = {NULL, 0};
    ConversionResult conversion_result;
    const char *program_name = "program";
    int exit_status = EXIT_SUCCESS;

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc < 3 || argv == NULL || argv[1] == NULL) {
        if (fprintf(
                stderr,
                "Usage: %s string element [element ...]\n",
                program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    tuple.length = (size_t)(argc - 2);

    if (tuple.length > SIZE_MAX / sizeof(*tuple.items)) {
        return EXIT_FAILURE;
    }

    tuple.items = calloc(tuple.length, sizeof(*tuple.items));
    if (tuple.items == NULL) {
        return EXIT_FAILURE;
    }

    string.data = argv[1];
    string.length = string_length(argv[1]);

    for (size_t i = 0; i < tuple.length; ++i) {
        if (argv[i + 2] == NULL) {
            free(tuple.items);
            return EXIT_FAILURE;
        }

        tuple.items[i].data = argv[i + 2];
        tuple.items[i].length = string_length(argv[i + 2]);
    }

    conversion_result = tuple_to_list(&tuple, &string, &list);

    free(tuple.items);
    tuple.items = NULL;
    tuple.length = 0;

    if (conversion_result != CONVERSION_SUCCESS) {
        if (fprintf(stderr, "Failed to convert tuple to list\n") < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list.length; ++i) {
        if (puts(list.items[i]) == EOF) {
            exit_status = EXIT_FAILURE;
            break;
        }
    }

    free_list(&list);

    return exit_status;
}