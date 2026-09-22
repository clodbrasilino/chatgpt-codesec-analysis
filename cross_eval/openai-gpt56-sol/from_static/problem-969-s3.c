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
    size_t initial_length;
    char **values;
    size_t count;
    size_t capacity;
} JoinedTuple;

static int bounded_string_length(const char *string, size_t string_size,
                                 size_t *length)
{
    const char *terminator;

    if (string == NULL || string_size == 0U || length == NULL) {
        return -1;
    }

    terminator = memchr(string, '\0', string_size);
    if (terminator == NULL) {
        return -1;
    }

    *length = (size_t)(terminator - string);
    return 0;
}

static int duplicate_bounded_string(const char *source, size_t source_size,
                                    char **destination,
                                    size_t *destination_length)
{
    size_t length;
    char *copy;

    if (destination == NULL || destination_length == NULL) {
        return -1;
    }

    *destination = NULL;
    *destination_length = 0U;

    if (bounded_string_length(source, source_size, &length) != 0) {
        return -1;
    }

    if (length > SIZE_MAX - 1U) {
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
    *destination_length = length;
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

static int reserve_values(JoinedTuple *tuple, size_t required_capacity)
{
    size_t new_capacity;
    char **new_values;

    if (tuple == NULL) {
        return -1;
    }

    if (required_capacity <= tuple->capacity) {
        return 0;
    }

    new_capacity = tuple->capacity == 0U ? 2U : tuple->capacity;

    while (new_capacity < required_capacity) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required_capacity;
            break;
        }
        new_capacity *= 2U;
    }

    if (new_capacity < required_capacity ||
        new_capacity > SIZE_MAX / sizeof(*new_values)) {
        return -1;
    }

    new_values = realloc(tuple->values,
                         new_capacity * sizeof(*new_values));
    if (new_values == NULL) {
        return -1;
    }

    tuple->values = new_values;
    tuple->capacity = new_capacity;
    return 0;
}

static int append_value(JoinedTuple *tuple, const char *value,
                        size_t value_size)
{
    char *copy;
    size_t copy_length;

    if (tuple == NULL || tuple->count == SIZE_MAX) {
        return -1;
    }

    if (duplicate_bounded_string(value, value_size, &copy,
                                 &copy_length) != 0) {
        return -1;
    }

    if (reserve_values(tuple, tuple->count + 1U) != 0) {
        free(copy);
        return -1;
    }

    tuple->values[tuple->count] = copy;
    ++tuple->count;
    return 0;
}

static int bounded_strings_equal(const char *left, size_t left_size,
                                 const char *right, size_t right_size,
                                 int *equal)
{
    size_t left_length;
    size_t right_length;

    if (equal == NULL) {
        return -1;
    }

    *equal = 0;

    if (bounded_string_length(left, left_size, &left_length) != 0 ||
        bounded_string_length(right, right_size, &right_length) != 0) {
        return -1;
    }

    if (left_length != right_length) {
        return 0;
    }

    if (left_length == 0U ||
        memcmp(left, right, left_length) == 0) {
        *equal = 1;
    }

    return 0;
}

static int reserve_groups(JoinedTuple **result, size_t *capacity,
                          size_t required_capacity)
{
    size_t new_capacity;
    JoinedTuple *new_result;

    if (result == NULL || capacity == NULL) {
        return -1;
    }

    if (required_capacity <= *capacity) {
        return 0;
    }

    new_capacity = *capacity == 0U ? 4U : *capacity;

    while (new_capacity < required_capacity) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required_capacity;
            break;
        }
        new_capacity *= 2U;
    }

    if (new_capacity < required_capacity ||
        new_capacity > SIZE_MAX / sizeof(*new_result)) {
        return -1;
    }

    new_result = realloc(*result,
                         new_capacity * sizeof(*new_result));
    if (new_result == NULL) {
        return -1;
    }

    *result = new_result;
    *capacity = new_capacity;
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
         (input == NULL || initial_sizes == NULL ||
          value_sizes == NULL))) {
        return -1;
    }

    *output = NULL;
    *output_count = 0U;

    for (i = 0U; i < input_count; ++i) {
        size_t initial_length;
        size_t value_length;
        size_t group;

        if (bounded_string_length(input[i].initial, initial_sizes[i],
                                  &initial_length) != 0 ||
            bounded_string_length(input[i].value, value_sizes[i],
                                  &value_length) != 0) {
            free_joined_tuples(result, result_count);
            return -1;
        }

        for (group = 0U; group < result_count; ++group) {
            int equal;

            if (bounded_strings_equal(result[group].initial,
                                      result[group].initial_length + 1U,
                                      input[i].initial,
                                      initial_sizes[i],
                                      &equal) != 0) {
                free_joined_tuples(result, result_count);
                return -1;
            }

            if (equal != 0) {
                break;
            }
        }

        if (group == result_count) {
            JoinedTuple *new_group;

            if (result_count == SIZE_MAX ||
                reserve_groups(&result, &result_capacity,
                               result_count + 1U) != 0) {
                free_joined_tuples(result, result_count);
                return -1;
            }

            new_group = &result[result_count];
            new_group->initial = NULL;
            new_group->initial_length = 0U;
            new_group->values = NULL;
            new_group->count = 0U;
            new_group->capacity = 0U;

            if (duplicate_bounded_string(input[i].initial,
                                         initial_sizes[i],
                                         &new_group->initial,
                                         &new_group->initial_length) != 0) {
                free_joined_tuples(result, result_count);
                return -1;
            }

            group = result_count;
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