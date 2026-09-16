#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t length;
} Tuple;

typedef struct {
    Tuple first;
    Tuple second;
} NestedTuple;

static void free_tuple(Tuple *tuple)
{
    free(tuple->values);
    tuple->values = NULL;
    tuple->length = 0;
}

static int copy_tuple(Tuple *destination, const Tuple *source)
{
    destination->values = NULL;
    destination->length = 0;

    if (source->length == 0) {
        return 0;
    }

    if (source->values == NULL ||
        source->length > SIZE_MAX / sizeof(*destination->values)) {
        return -1;
    }

    destination->values = malloc(source->length * sizeof(*destination->values));
    if (destination->values == NULL) {
        return -1;
    }

    for (size_t i = 0; i < source->length; ++i) {
        destination->values[i] = source->values[i];
    }

    destination->length = source->length;
    return 0;
}

static int concatenate_to_nested_tuple(
    NestedTuple *result,
    const Tuple *first,
    const Tuple *second)
{
    if (result == NULL || first == NULL || second == NULL) {
        return -1;
    }

    result->first.values = NULL;
    result->first.length = 0;
    result->second.values = NULL;
    result->second.length = 0;

    if (copy_tuple(&result->first, first) != 0) {
        return -1;
    }

    if (copy_tuple(&result->second, second) != 0) {
        free_tuple(&result->first);
        return -1;
    }

    return 0;
}

static void free_nested_tuple(NestedTuple *tuple)
{
    if (tuple != NULL) {
        free_tuple(&tuple->first);
        free_tuple(&tuple->second);
    }
}

static int print_tuple(const Tuple *tuple)
{
    if (tuple == NULL || (tuple->length != 0 && tuple->values == NULL)) {
        return -1;
    }

    if (putchar('(') == EOF) {
        return -1;
    }

    for (size_t i = 0; i < tuple->length; ++i) {
        if (i != 0 && printf(", ") < 0) {
            return -1;
        }
        if (printf("%d", tuple->values[i]) < 0) {
            return -1;
        }
    }

    if (putchar(')') == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    int first_values[] = {1, 2, 3};
    int second_values[] = {4, 5};
    const Tuple first = {
        first_values,
        sizeof(first_values) / sizeof(first_values[0])
    };
    const Tuple second = {
        second_values,
        sizeof(second_values) / sizeof(second_values[0])
    };
    NestedTuple result;

    if (concatenate_to_nested_tuple(&result, &first, &second) != 0) {
        fputs("Failed to create nested tuple.\n", stderr);
        return EXIT_FAILURE;
    }

    if (putchar('(') == EOF ||
        print_tuple(&result.first) != 0 ||
        printf(", ") < 0 ||
        print_tuple(&result.second) != 0 ||
        printf(")\n") < 0) {
        free_nested_tuple(&result);
        return EXIT_FAILURE;
    }

    free_nested_tuple(&result);
    return EXIT_SUCCESS;
}