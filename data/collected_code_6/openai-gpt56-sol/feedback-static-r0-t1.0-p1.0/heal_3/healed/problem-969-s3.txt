#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *initial;
    const char *value;
} Tuple;

typedef struct {
    char *initial;
    char **values;
    size_t count;
    size_t capacity;
} JoinedTuple;

static int duplicate_string(const char *source, size_t source_size,
                            char **destination)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || source_size == 0U || destination == NULL) {
        return -1;
    }

    *destination = NULL;

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return -1;
    }

    length = (size_t)(terminator - source);

    if (length == SIZE_MAX) {
        return -1;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return -1;
    }

    if (length != 0U) {
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    *destination = copy;
    return 0;
}

static void free_joined_tuples(JoinedTuple *tuples, size_t count)
{
    size_t i;

    if (tuples == NULL) {
        return;
    }

    for (i = 0U; i < count; ++i) {
        size_t j;

        free(tuples[i].initial);

        for (j = 0U; j < tuples[i].count; ++j) {
            free(tuples[i].values[j]);
        }

        free(tuples[i].values);
    }

    free(tuples);
}

static int append_value(JoinedTuple *tuple, const char *value,
                        size_t value_size)
{
    char *copy;

    if (tuple == NULL || value == NULL || value_size == 0U) {
        return -1;
    }

    if (tuple->count == tuple->capacity) {
        size_t new_capacity;
        char **new_values;

        if (tuple->capacity == 0U) {
            new_capacity = 2U;
        } else {
            if (tuple->capacity > SIZE_MAX / 2U) {
                return -1;
            }
            new_capacity = tuple->capacity * 2U;
        }

        if (new_capacity > SIZE_MAX / sizeof(*new_values)) {
            return -1;
        }

        new_values = realloc(tuple->values,
                             new_capacity * sizeof(*new_values));
        if (new_values == NULL) {
            return -1;
        }

        tuple->values = new_values;
        tuple->capacity = new_capacity;
    }

    if (duplicate_string(value, value_size, &copy) != 0) {
        return -1;
    }

    tuple->values[tuple->count] = copy;
    ++tuple->count;

    return 0;
}

static int strings_equal(const char *left, const char *right,
                         size_t right_size, int *equal)
{
    const char *terminator;
    size_t right_length;
    size_t left_length;

    if (left == NULL || right == NULL || right_size == 0U || equal == NULL) {
        return -1;
    }

    *equal = 0;

    terminator = memchr(right, '\0', right_size);
    if (terminator == NULL) {
        return -1;
    }

    right_length = (size_t)(terminator - right);
    left_length = strlen(left);

    if (left_length == right_length &&
        memcmp(left, right, right_length) == 0) {
        *equal = 1;
    }

    return 0;
}

static int join_tuples(const Tuple *input, const size_t *initial_sizes,
                       const size_t *value_sizes, size_t input_count,
                       JoinedTuple **output, size_t *output_count)
{
    JoinedTuple *result = NULL;
    size_t result_count = 0U;
    size_t result_capacity = 0U;
    size_t i;

    if (output == NULL || output_count == NULL ||
        (input_count != 0U &&
         (input == NULL || initial_sizes == NULL || value_sizes == NULL))) {
        return -1;
    }

    *output = NULL;
    *output_count = 0U;

    for (i = 0U; i < input_count; ++i) {
        size_t group;

        if (input[i].initial == NULL || input[i].value == NULL ||
            initial_sizes[i] == 0U || value_sizes[i] == 0U) {
            free_joined_tuples(result, result_count);
            return -1;
        }

        for (group = 0U; group < result_count; ++group) {
            int equal;

            if (strings_equal(result[group].initial, input[i].initial,
                              initial_sizes[i], &equal) != 0) {
                free_joined_tuples(result, result_count);
                return -1;
            }

            if (equal != 0) {
                break;
            }
        }

        if (group == result_count) {
            if (result_count == result_capacity) {
                size_t new_capacity;
                JoinedTuple *new_result;

                if (result_capacity == 0U) {
                    new_capacity = 4U;
                } else {
                    if (result_capacity > SIZE_MAX / 2U) {
                        free_joined_tuples(result, result_count);
                        return -1;
                    }
                    new_capacity = result_capacity * 2U;
                }

                if (new_capacity > SIZE_MAX / sizeof(*new_result)) {
                    free_joined_tuples(result, result_count);
                    return -1;
                }

                new_result = realloc(result,
                                     new_capacity * sizeof(*new_result));
                if (new_result == NULL) {
                    free_joined_tuples(result, result_count);
                    return -1;
                }

                result = new_result;
                result_capacity = new_capacity;
            }

            result[group].initial = NULL;
            result[group].values = NULL;
            result[group].count = 0U;
            result[group].capacity = 0U;

            if (duplicate_string(input[i].initial, initial_sizes[i],
                                 &result[group].initial) != 0) {
                free_joined_tuples(result, result_count);
                return -1;
            }

            ++result_count;
        }

        if (append_value(&result[group], input[i].value,
                         value_sizes[i]) != 0) {
            free_joined_tuples(result, result_count);
            return -1;
        }
    }

    *output = result;
    *output_count = result_count;
    return 0;
}

int main(void)
{
    static const Tuple input[] = {
        {"A", "apple"},
        {"B", "banana"},
        {"A", "apricot"},
        {"C", "cherry"},
        {"B", "blueberry"}
    };
    static const size_t initial_sizes[] = {
        sizeof("A"),
        sizeof("B"),
        sizeof("A"),
        sizeof("C"),
        sizeof("B")
    };
    static const size_t value_sizes[] = {
        sizeof("apple"),
        sizeof("banana"),
        sizeof("apricot"),
        sizeof("cherry"),
        sizeof("blueberry")
    };
    JoinedTuple *joined = NULL;
    size_t joined_count = 0U;
    size_t i;

    if (join_tuples(input, initial_sizes, value_sizes,
                    sizeof(input) / sizeof(input[0]),
                    &joined, &joined_count) != 0) {
        fputs("Failed to join tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < joined_count; ++i) {
        size_t j;

        if (printf("(%s", joined[i].initial) < 0) {
            free_joined_tuples(joined, joined_count);
            return EXIT_FAILURE;
        }

        for (j = 0U; j < joined[i].count; ++j) {
            if (printf(", %s", joined[i].values[j]) < 0) {
                free_joined_tuples(joined, joined_count);
                return EXIT_FAILURE;
            }
        }

        if (puts(")") == EOF) {
            free_joined_tuples(joined, joined_count);
            return EXIT_FAILURE;
        }
    }

    free_joined_tuples(joined, joined_count);
    return EXIT_SUCCESS;
}