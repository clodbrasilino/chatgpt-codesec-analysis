#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    const int *elements;
    size_t length;
} TupleView;

typedef struct {
    int *elements;
    size_t length;
} Tuple;

typedef enum {
    JOIN_SUCCESS,
    JOIN_INVALID_ARGUMENT,
    JOIN_ALLOCATION_FAILURE,
    JOIN_SIZE_OVERFLOW
} JoinStatus;

static void free_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(tuples[i].elements);
    }

    free(tuples);
}

static JoinStatus join_tuples(const TupleView *input,
                              size_t input_count,
                              Tuple **output,
                              size_t *output_count)
{
    Tuple *joined = NULL;
    size_t joined_count = 0;

    if (output == NULL || output_count == NULL) {
        return JOIN_INVALID_ARGUMENT;
    }

    *output = NULL;
    *output_count = 0;

    if (input_count == 0) {
        return JOIN_SUCCESS;
    }

    if (input == NULL) {
        return JOIN_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i < input_count; ++i) {
        if (input[i].elements == NULL || input[i].length == 0) {
            return JOIN_INVALID_ARGUMENT;
        }

        if (input[i].length > SIZE_MAX / sizeof(int)) {
            return JOIN_SIZE_OVERFLOW;
        }
    }

    if (input_count > SIZE_MAX / sizeof(*joined)) {
        return JOIN_SIZE_OVERFLOW;
    }

    joined = calloc(input_count, sizeof(*joined));
    if (joined == NULL) {
        return JOIN_ALLOCATION_FAILURE;
    }

    for (size_t i = 0; i < input_count; ++i) {
        size_t group = joined_count;

        for (size_t j = 0; j < joined_count; ++j) {
            if (joined[j].elements[0] == input[i].elements[0]) {
                group = j;
                break;
            }
        }

        if (group == joined_count) {
            size_t bytes = input[i].length * sizeof(int);

            joined[group].elements = malloc(bytes);
            if (joined[group].elements == NULL) {
                free_tuples(joined, joined_count);
                return JOIN_ALLOCATION_FAILURE;
            }

            memcpy(joined[group].elements, input[i].elements, bytes);
            joined[group].length = input[i].length;
            ++joined_count;
        } else {
            size_t additional = input[i].length - 1;

            if (additional == 0) {
                continue;
            }

            if (joined[group].length > SIZE_MAX - additional) {
                free_tuples(joined, joined_count);
                return JOIN_SIZE_OVERFLOW;
            }

            size_t new_length = joined[group].length + additional;

            if (new_length > SIZE_MAX / sizeof(int)) {
                free_tuples(joined, joined_count);
                return JOIN_SIZE_OVERFLOW;
            }

            int *resized = realloc(joined[group].elements,
                                   new_length * sizeof(int));
            if (resized == NULL) {
                free_tuples(joined, joined_count);
                return JOIN_ALLOCATION_FAILURE;
            }

            joined[group].elements = resized;
            memcpy(joined[group].elements + joined[group].length,
                   input[i].elements + 1,
                   additional * sizeof(int));
            joined[group].length = new_length;
        }
    }

    *output = joined;
    *output_count = joined_count;
    return JOIN_SUCCESS;
}

static void print_tuples(const Tuple *tuples, size_t count)
{
    printf("[");

    for (size_t i = 0; i < count; ++i) {
        printf("(");

        for (size_t j = 0; j < tuples[i].length; ++j) {
            printf("%d", tuples[i].elements[j]);

            if (j + 1 < tuples[i].length) {
                printf(", ");
            }
        }

        printf(")");

        if (i + 1 < count) {
            printf(", ");
        }
    }

    printf("]\n");
}

int main(void)
{
    static const int values1[] = {5, 6};
    static const int values2[] = {5, 7};
    static const int values3[] = {5, 8};
    static const int values4[] = {6, 10};
    static const int values5[] = {7, 13};

    const TupleView input[] = {
        {values1, sizeof(values1) / sizeof(values1[0])},
        {values2, sizeof(values2) / sizeof(values2[0])},
        {values3, sizeof(values3) / sizeof(values3[0])},
        {values4, sizeof(values4) / sizeof(values4[0])},
        {values5, sizeof(values5) / sizeof(values5[0])}
    };

    Tuple *joined = NULL;
    size_t joined_count = 0;
    JoinStatus status = join_tuples(input,
                                    sizeof(input) / sizeof(input[0]),
                                    &joined,
                                    &joined_count);

    if (status != JOIN_SUCCESS) {
        fprintf(stderr, "Unable to join tuples: error %d\n", (int)status);
        return EXIT_FAILURE;
    }

    print_tuples(joined, joined_count);
    free_tuples(joined, joined_count);

    return EXIT_SUCCESS;
}