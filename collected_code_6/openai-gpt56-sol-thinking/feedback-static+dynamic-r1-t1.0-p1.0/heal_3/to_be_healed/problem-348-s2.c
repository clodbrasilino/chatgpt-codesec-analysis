#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t sum;
    uint64_t count;
} State;

typedef enum {
    COUNT_SUCCESS,
    COUNT_INVALID_ARGUMENT,
    COUNT_MEMORY_ERROR,
    COUNT_OVERFLOW
} CountStatus;

typedef struct {
    FILE *stream;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    size_t position;
    size_t length;
    int exhausted;
    int error;
} Input;

static void input_init(Input *input, FILE *stream)
{
    input->stream = stream;
    input->position = 0;
    input->length = 0;
    input->exhausted = 0;
    input->error = 0;
}

static int input_read_char(Input *input, int *character)
{
    if (input == NULL || character == NULL || input->stream == NULL) {
        return 0;
    }

    if (input->position == input->length) {
        size_t bytes_read;

        if (input->exhausted) {
            return 0;
        }

        bytes_read = fread(input->buffer,
                           sizeof(input->buffer[0]),
                           sizeof(input->buffer),
                           input->stream);

        input->position = 0;
        input->length = bytes_read;

        if (bytes_read == 0) {
            input->exhausted = 1;
            if (ferror(input->stream)) {
                input->error = 1;
            }
            return 0;
        }
    }

    *character = input->buffer[input->position++];
    return 1;
}

static int input_failed(const Input *input)
{
    return input != NULL && input->error;
}

static int read_size_value(Input *input, size_t *result)
{
    size_t value = 0;
    int character;
    int valid = 1;
    int has_digit = 0;

    if (input == NULL || result == NULL) {
        return 0;
    }

    do {
        if (!input_read_char(input, &character)) {
            return 0;
        }
    } while (isspace((unsigned char)character));

    if (character == '+' || character == '-') {
        if (character == '-') {
            valid = 0;
        }

        if (!input_read_char(input, &character)) {
            return 0;
        }
    }

    for (;;) {
        if (isspace((unsigned char)character)) {
            break;
        }

        if (character < '0' || character > '9') {
            valid = 0;
        } else {
            size_t digit = (size_t)(character - '0');

            has_digit = 1;

            if (valid) {
                if (value > (SIZE_MAX - digit) / (size_t)10) {
                    valid = 0;
                } else {
                    value = value * (size_t)10 + digit;
                }
            }
        }

        if (!input_read_char(input, &character)) {
            if (input_failed(input)) {
                return 0;
            }
            break;
        }
    }

    if (!valid || !has_digit) {
        return 0;
    }

    *result = value;
    return 1;
}

static int read_int64_value(Input *input, int64_t *result)
{
    uint64_t magnitude = 0;
    uint64_t limit;
    int character;
    int negative = 0;
    int valid = 1;
    int has_digit = 0;

    if (input == NULL || result == NULL) {
        return 0;
    }

    do {
        if (!input_read_char(input, &character)) {
            return 0;
        }
    } while (isspace((unsigned char)character));

    if (character == '+' || character == '-') {
        negative = character == '-';

        if (!input_read_char(input, &character)) {
            return 0;
        }
    }

    limit = negative
                ? (uint64_t)INT64_MAX + UINT64_C(1)
                : (uint64_t)INT64_MAX;

    for (;;) {
        if (isspace((unsigned char)character)) {
            break;
        }

        if (character < '0' || character > '9') {
            valid = 0;
        } else {
            uint64_t digit = (uint64_t)(character - '0');

            has_digit = 1;

            if (valid) {
                if (magnitude > (limit - digit) / UINT64_C(10)) {
                    valid = 0;
                } else {
                    magnitude = magnitude * UINT64_C(10) + digit;
                }
            }
        }

        if (!input_read_char(input, &character)) {
            if (input_failed(input)) {
                return 0;
            }
            break;
        }
    }

    if (!valid || !has_digit) {
        return 0;
    }

    if (negative) {
        if (magnitude == (uint64_t)INT64_MAX + UINT64_C(1)) {
            *result = INT64_MIN;
        } else {
            *result = -(int64_t)magnitude;
        }
    } else {
        *result = (int64_t)magnitude;
    }

    return 1;
}

static int compare_states(const void *left, const void *right)
{
    const State *a = left;
    const State *b = right;

    if (a->sum < b->sum) {
        return -1;
    }

    if (a->sum > b->sum) {
        return 1;
    }

    return 0;
}

static int add_int64_checked(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return 0;
    }

    *result = left + right;
    return 1;
}

CountStatus count_sequences(const int64_t *values,
                            size_t value_count,
                            size_t sequence_length,
                            uint64_t *result)
{
    State *states;
    size_t state_count = 1;
    size_t position;

    if (result == NULL || (values == NULL && value_count != 0)) {
        return COUNT_INVALID_ARGUMENT;
    }

    *result = 0;

    if (sequence_length == 0) {
        *result = UINT64_C(1);
        return COUNT_SUCCESS;
    }

    if (value_count == 0) {
        return COUNT_SUCCESS;
    }

    states = malloc(sizeof(*states));
    if (states == NULL) {
        return COUNT_MEMORY_ERROR;
    }

    states[0].sum = 0;
    states[0].count = UINT64_C(1);

    for (position = 0; position < sequence_length; ++position) {
        State *candidates;
        size_t capacity;
        size_t candidate_count = 0;
        size_t merged_count = 0;
        size_t i;
        size_t j;

        if (state_count > SIZE_MAX / value_count) {
            free(states);
            return COUNT_MEMORY_ERROR;
        }

        capacity = state_count * value_count;

        if (capacity > SIZE_MAX / sizeof(*candidates)) {
            free(states);
            return COUNT_MEMORY_ERROR;
        }

        candidates = malloc(capacity * sizeof(*candidates));
        if (candidates == NULL) {
            free(states);
            return COUNT_MEMORY_ERROR;
        }

        for (i = 0; i < state_count; ++i) {
            for (j = 0; j < value_count; ++j) {
                int64_t next_sum;

                if (!add_int64_checked(states[i].sum,
                                       values[j],
                                       &next_sum)) {
                    free(candidates);
                    free(states);
                    return COUNT_OVERFLOW;
                }

                if (next_sum >= 0) {
                    candidates[candidate_count].sum = next_sum;
                    candidates[candidate_count].count = states[i].count;
                    ++candidate_count;
                }
            }
        }

        free(states);

        if (candidate_count == 0) {
            free(candidates);
            return COUNT_SUCCESS;
        }

        qsort(candidates,
              candidate_count,
              sizeof(*candidates),
              compare_states);

        for (i = 0; i < candidate_count; ++i) {
            if (merged_count != 0 &&
                candidates[merged_count - 1].sum == candidates[i].sum) {
                if (UINT64_MAX - candidates[merged_count - 1].count <
                    candidates[i].count) {
                    free(candidates);
                    return COUNT_OVERFLOW;
                }

                candidates[merged_count - 1].count += candidates[i].count;
            } else {
                candidates[merged_count] = candidates[i];
                ++merged_count;
            }
        }

        states = candidates;
        state_count = merged_count;
    }

    for (position = 0; position < state_count; ++position) {
        if (UINT64_MAX - *result < states[position].count) {
            free(states);
            *result = 0;
            return COUNT_OVERFLOW;
        }

        *result += states[position].count;
    }

    free(states);
    return COUNT_SUCCESS;
}

int main(void)
{
    Input input;
    int64_t *values = NULL;
    size_t value_count;
    size_t sequence_length;
    size_t i;
    uint64_t result;
    CountStatus status;

    input_init(&input, stdin);

    if (!read_size_value(&input, &value_count) ||
        !read_size_value(&input, &sequence_length)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (value_count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    if (value_count != 0) {
        values = malloc(value_count * sizeof(*values));
        if (values == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < value_count; ++i) {
        if (!read_int64_value(&input, &values[i])) {
            fprintf(stderr, "Invalid input\n");
            free(values);
            return EXIT_FAILURE;
        }
    }

    status = count_sequences(values,
                             value_count,
                             sequence_length,
                             &result);

    free(values);

    switch (status) {
        case COUNT_SUCCESS:
            printf("%" PRIu64 "\n", result);
            return EXIT_SUCCESS;

        case COUNT_MEMORY_ERROR:
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;

        case COUNT_OVERFLOW:
            fprintf(stderr, "Numeric overflow\n");
            return EXIT_FAILURE;

        case COUNT_INVALID_ARGUMENT:
        default:
            fprintf(stderr, "Invalid argument\n");
            return EXIT_FAILURE;
    }
}