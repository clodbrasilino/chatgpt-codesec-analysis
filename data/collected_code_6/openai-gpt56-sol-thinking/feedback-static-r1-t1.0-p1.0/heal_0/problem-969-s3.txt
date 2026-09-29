#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

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

static bool join_tuples(const Tuple *input, size_t input_count,
                        Tuple **output, size_t *output_count)
{
    Tuple *result = NULL;
    size_t unique_count = 0;
    size_t group_index = 0;

    if (output == NULL || output_count == NULL) {
        return false;
    }

    *output = NULL;
    *output_count = 0;

    if (input_count == 0) {
        return true;
    }

    if (input == NULL) {
        return false;
    }

    for (size_t i = 0; i < input_count; ++i) {
        if (input[i].elements == NULL || input[i].length == 0) {
            return false;
        }
    }

    for (size_t i = 0; i < input_count; ++i) {
        bool previously_seen = false;

        for (size_t j = 0; j < i; ++j) {
            if (input[j].elements[0] == input[i].elements[0]) {
                previously_seen = true;
                break;
            }
        }

        if (!previously_seen) {
            ++unique_count;
        }
    }

    if (unique_count > SIZE_MAX / sizeof(*result)) {
        return false;
    }

    result = calloc(unique_count, sizeof(*result));
    if (result == NULL) {
        return false;
    }

    for (size_t i = 0; i < input_count; ++i) {
        bool previously_seen = false;
        size_t joined_length = 1;
        size_t position = 1;

        for (size_t j = 0; j < i; ++j) {
            if (input[j].elements[0] == input[i].elements[0]) {
                previously_seen = true;
                break;
            }
        }

        if (previously_seen) {
            continue;
        }

        for (size_t j = i; j < input_count; ++j) {
            if (input[j].elements[0] == input[i].elements[0]) {
                size_t tail_length = input[j].length - 1;

                if (tail_length > SIZE_MAX - joined_length) {
                    free_tuples(result, unique_count);
                    return false;
                }

                joined_length += tail_length;
            }
        }

        if (joined_length > SIZE_MAX / sizeof(*result[group_index].elements)) {
            free_tuples(result, unique_count);
            return false;
        }

        result[group_index].elements =
            malloc(joined_length * sizeof(*result[group_index].elements));

        if (result[group_index].elements == NULL) {
            free_tuples(result, unique_count);
            return false;
        }

        result[group_index].length = joined_length;
        result[group_index].elements[0] = input[i].elements[0];

        for (size_t j = i; j < input_count; ++j) {
            if (input[j].elements[0] == input[i].elements[0]) {
                for (size_t k = 1; k < input[j].length; ++k) {
                    result[group_index].elements[position++] =
                        input[j].elements[k];
                }
            }
        }

        ++group_index;
    }

    *output = result;
    *output_count = unique_count;
    return true;
}

static bool print_tuples(const Tuple *tuples, size_t count)
{
    if (putchar('[') == EOF) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        if (i > 0 && printf(", ") < 0) {
            return false;
        }

        if (putchar('(') == EOF) {
            return false;
        }

        for (size_t j = 0; j < tuples[i].length; ++j) {
            if (j > 0 && printf(", ") < 0) {
                return false;
            }

            if (printf("%d", tuples[i].elements[j]) < 0) {
                return false;
            }
        }

        if (tuples[i].length == 1 && putchar(',') == EOF) {
            return false;
        }

        if (putchar(')') == EOF) {
            return false;
        }
    }

    return printf("]\n") >= 0;
}

int main(void)
{
    int first[] = {5, 6};
    int second[] = {5, 7};
    int third[] = {5, 8};
    int fourth[] = {6, 10};
    int fifth[] = {7, 13};

    Tuple input[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])},
        {fourth, sizeof(fourth) / sizeof(fourth[0])},
        {fifth, sizeof(fifth) / sizeof(fifth[0])}
    };

    Tuple *joined = NULL;
    size_t joined_count = 0;

    if (!join_tuples(input, sizeof(input) / sizeof(input[0]),
                     &joined, &joined_count)) {
        return EXIT_FAILURE;
    }

    if (!print_tuples(joined, joined_count)) {
        free_tuples(joined, joined_count);
        return EXIT_FAILURE;
    }

    free_tuples(joined, joined_count);
    return EXIT_SUCCESS;
}