#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

typedef struct {
    char **values;
    size_t size;
} StringTuple;

typedef struct {
    int *values;
    size_t size;
} IntTuple;

static int string_to_int(const char *str, int *out) {
    char *endptr;
    long val;

    errno = 0;
    val = strtol(str, &endptr, 10);

    if (errno != 0 || endptr == str || *endptr != '\0') {
        return -1;
    }

    if (val > INT_MAX || val < INT_MIN) {
        return -1;
    }

    *out = (int)val;
    return 0;
}

int convert_string_tuple_to_int_tuple(const StringTuple *input, IntTuple *output) {
    if (input == NULL || output == NULL) {
        return -1;
    }

    if (input->values == NULL || input->size == 0) {
        output->values = NULL;
        output->size = 0;
        return 0;
    }

    int *int_values = malloc(input->size * sizeof(int));
    if (int_values == NULL) {
        return -1;
    }

    for (size_t i = 0; i < input->size; i++) {
        if (string_to_int(input->values[i], &int_values[i]) != 0) {
            free(int_values);
            return -1;
        }
    }

    output->values = int_values;
    output->size = input->size;
    return 0;
}

void free_int_tuple(IntTuple *tuple) {
    if (tuple != NULL && tuple->values != NULL) {
        free(tuple->values);
        tuple->values = NULL;
        tuple->size = 0;
    }
}

int main(void) {
    char *test_strings[] = {"10", "20", "30", "40", "50"};
    StringTuple str_tuple = {test_strings, 5};
    IntTuple int_tuple;

    if (convert_string_tuple_to_int_tuple(&str_tuple, &int_tuple) == 0) {
        printf("Converted tuple: ");
        for (size_t i = 0; i < int_tuple.size; i++) {
            printf("%d ", int_tuple.values[i]);
        }
        printf("\n");
        free_int_tuple(&int_tuple);
    } else {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}