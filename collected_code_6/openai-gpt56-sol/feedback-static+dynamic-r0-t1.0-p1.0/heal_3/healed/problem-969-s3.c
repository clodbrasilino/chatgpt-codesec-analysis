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

static int duplicate_string(const char *source, size_t max_length,
                            char **destination)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || destination == NULL || max_length == 0U) {
        return -1;
    }

    *destination = NULL;

    terminator = memchr(source, '\0', max_length);
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
    size_t j;

    if (tuples == NULL) {
        return;
    }

    for (i = 0U; i < count; ++i) {
        free(tuples[i].initial);

        for (j = 0U; j < tuples[i].count; ++j) {
            free(tuples[i].values[j]);
        }

        free(tuples[i].values);
    }

    free(tuples);
}

static int append_value(JoinedTuple *tuple, const char *value,
                        size_t value_max_length)
{
    char *copy;

    if (tuple == NULL || value == NULL || value_max_length == 0U) {
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

    if (duplicate_string(value, value_max_length, &copy) != 0) {
        return -1;
    }

    tuple->values[tuple->count] = copy;
    ++tuple->count;

    return 0;
}

static int grow_results(JoinedTuple **result, size_t *capacity)
{
    size_t new_capacity;
    JoinedTuple *new_result;

    if (result == NULL || capacity == NULL) {
        return -1;
    }

    if (*capacity == 0U) {
        new_capacity = 4U;
    } else {
        if (*capacity > SIZE_MAX / 2U) {
            return -1;
        }
        new_capacity = *capacity * 2U;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_result)) {
        return -1;
    }

    new_result = realloc(*result, new_capacity * sizeof(*new_result));
    if (new_result == NULL) {
        return -1;
    }

    *result = new_result;
    *capacity = new_capacity;

    return 0;
}

static int join_tuples(const Tuple *input, size_t input_count,
                       size_t initial_max_length, size_t value_max_length,
                       JoinedTuple **output, size_t *output_count)
{
    JoinedTuple *result = NULL;
    size_t result_count = 0U;
    size_t result_capacity = 0U;
    size_t i;

    if (output == NULL || output_count == NULL ||
        initial_max_length == 0U || value_max_length == 0U ||
        (input == NULL && input_count != 0U)) {
        return -1;
    }

    *output = NULL;
    *output_count = 0U;

    for (i = 0U; i < input_count; ++i) {
        size_t group;
        const char *initial_end;
        size_t initial_length;

        if (input[i].initial == NULL || input[i].value == NULL) {
            free_joined_tuples(result, result_count);
            return -1;
        }

        initial_end = memchr(input[i].initial, '\0', initial_max_length);
        if (initial_end == NULL ||
            memchr(input[i].value, '\0', value_max_length) == NULL) {
            free_joined_tuples(result, result_count);
            return -1;
        }

        initial_length = (size_t)(initial_end - input[i].initial);

        for (group = 0U; group < result_count; ++group) {
            size_t stored_length = strlen(result[group].initial);

            if (stored_length == initial_length &&
                memcmp(result[group].initial, input[i].initial,
                       initial_length) == 0) {
                break;
            }
        }

        if (group == result_count) {
            if (result_count == result_capacity &&
                grow_results(&result, &result_capacity) != 0) {
                free_joined_tuples(result, result_count);
                return -1;
            }

            result[group].initial = NULL;
            result[group].values = NULL;
            result[group].count = 0U;
            result[group].capacity = 0U;

            if (duplicate_string(input[i].initial, initial_max_length,
                                 &result[group].initial) != 0) {
                free_joined_tuples(result, result_count);
                return -1;
            }

            ++result_count;
        }

        if (append_value(&result[group], input[i].value,
                         value_max_length) != 0) {
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
    const Tuple input[] = {
        {"A", "apple"},
        {"B", "banana"},
        {"A", "apricot"},
        {"C", "cherry"},
        {"B", "blueberry"}
    };
    JoinedTuple *joined = NULL;
    size_t joined_count = 0U;
    size_t i;
    size_t j;

    if (join_tuples(input, sizeof(input) / sizeof(input[0]),
                    64U, 1024U, &joined, &joined_count) != 0) {
        fputs("Failed to join tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < joined_count; ++i) {
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