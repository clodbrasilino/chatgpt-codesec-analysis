#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *string;
    int *list;
    size_t list_length;
} Tuple;

typedef enum {
    TUPLE_SUCCESS = 0,
    TUPLE_INVALID_ARGUMENT,
    TUPLE_ALLOCATION_FAILURE
} TupleStatus;

void tuple_destroy(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    free(tuple->list);
    free(tuple->string);
    free(tuple);
}

TupleStatus tuple_create(const char *string, size_t string_length,
                         const int *list, size_t list_length,
                         Tuple **out_tuple)
{
    Tuple *tuple;
    size_t i;

    if (out_tuple == NULL) {
        return TUPLE_INVALID_ARGUMENT;
    }

    *out_tuple = NULL;

    if (string == NULL || (list_length > 0 && list == NULL)) {
        return TUPLE_INVALID_ARGUMENT;
    }

    if (string_length == SIZE_MAX ||
        list_length > SIZE_MAX / sizeof(*tuple->list)) {
        return TUPLE_ALLOCATION_FAILURE;
    }

    tuple = calloc(1, sizeof(*tuple));
    if (tuple == NULL) {
        return TUPLE_ALLOCATION_FAILURE;
    }

    tuple->string = malloc(string_length + 1);
    if (tuple->string == NULL) {
        tuple_destroy(tuple);
        return TUPLE_ALLOCATION_FAILURE;
    }

    for (i = 0; i < string_length; ++i) {
        tuple->string[i] = string[i];
    }
    tuple->string[string_length] = '\0';

    if (list_length > 0) {
        tuple->list = malloc(list_length * sizeof(*tuple->list));
        if (tuple->list == NULL) {
            tuple_destroy(tuple);
            return TUPLE_ALLOCATION_FAILURE;
        }

        for (i = 0; i < list_length; ++i) {
            tuple->list[i] = list[i];
        }
    }

    tuple->list_length = list_length;
    *out_tuple = tuple;

    return TUPLE_SUCCESS;
}

int main(void)
{
    const char input_string[] = "example";
    const int input_list[] = {10, 20, 30, 40};
    const size_t input_string_length = sizeof(input_string) - 1;
    const size_t input_list_length =
        sizeof(input_list) / sizeof(input_list[0]);
    Tuple *tuple = NULL;
    TupleStatus status;
    size_t i;
    int result = EXIT_SUCCESS;

    status = tuple_create(input_string, input_string_length,
                          input_list, input_list_length, &tuple);
    if (status != TUPLE_SUCCESS) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    if (printf("(%s, [", tuple->string) < 0) {
        result = EXIT_FAILURE;
    }

    for (i = 0; result == EXIT_SUCCESS && i < tuple->list_length; ++i) {
        if (printf("%s%d", i == 0 ? "" : ", ", tuple->list[i]) < 0) {
            result = EXIT_FAILURE;
        }
    }

    if (result == EXIT_SUCCESS && printf("])\n") < 0) {
        result = EXIT_FAILURE;
    }

    tuple_destroy(tuple);
    return result;
}