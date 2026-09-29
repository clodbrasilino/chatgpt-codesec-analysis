#include <ctype.h>
#include <inttypes.h>
#include <stddef.h>
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
    int error;
} Input;

static void input_init(Input *input, FILE *stream)
{
    if (input == NULL) {
        return;
    }

    input->stream = stream;
    input->error = stream == NULL;
}

static int input_get(Input *input)
{
    int character;

    if (input == NULL || input->stream == NULL || input->error) {
        if (input != NULL) {
            input->error = 1;
        }
        return EOF;
    }

    character = fgetc(input->stream);

    if (character == EOF && ferror(input->stream)) {
        input->error = 1;
    }

    return character;
}

static int read_first_nonspace(Input *input)
{
    int character;

    do {
        character = input_get(input);
    } while (character != EOF &&
             isspace((unsigned char)character));

    return character;
}

static int read_size_value(Input *input, size_t *value)
{
    size_t parsed = 0;
    int character;
    int negative = 0;
    int has_digit = 0;
    int valid = 1;
    int overflow = 0;

    if (input == NULL || value == NULL) {
        return 0;
    }

    character = read_first_nonspace(input);
    if (character == EOF) {
        return 0;
    }

    if (character == '+' || character == '-') {
        negative = character == '-';
        character = input_get(input);
    }

    while (character != EOF &&
           !isspace((unsigned char)character)) {
        if (character >= '0' && character <= '9') {
            size_t digit = (size_t)(character - '0');

            has_digit = 1;

            if (!overflow) {
                if (parsed > (SIZE_MAX - digit) / (size_t)10) {
                    overflow = 1;
                } else {
                    parsed = parsed * (size_t)10 + digit;
                }
            }
        } else {
            valid = 0;
        }

        character = input_get(input);
    }

    if (input->error || !valid || !has_digit || negative || overflow) {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int read_int64_value(Input *input, int64_t *value)
{
    uint64_t parsed = 0;
    uint64_t limit;
    int character;
    int negative = 0;
    int has_digit = 0;
    int valid = 1;
    int overflow = 0;

    if (input == NULL || value == NULL) {
        return 0;
    }

    character = read_first_nonspace(input);
    if (character == EOF) {
        return 0;
    }

    if (character == '+' || character == '-') {
        negative = character == '-';
        character = input_get(input);
    }

    limit = negative
        ? (uint64_t)INT64_MAX + UINT64_C(1)
        : (uint64_t)INT64_MAX;

    while (character != EOF &&
           !isspace((unsigned char)character)) {
        if (character >= '0' && character <= '9') {
            uint64_t digit = (uint64_t)(character - '0');

            has_digit = 1;

            if (!overflow) {
                if (parsed > (limit - digit) / UINT64_C(10)) {
                    overflow = 1;
                } else {
                    parsed = parsed * UINT64_C(10) + digit;
                }
            }
        } else {
            valid = 0;
        }

        character = input_get(input);
    }

    if (input->error || !valid || !has_digit || overflow) {
        return 0;
    }

    if (negative) {
        if (parsed == (uint64_t)INT64_MAX + UINT64_C(1)) {
            *value = INT64_MIN;
        } else {
            *value = -(int64_t)parsed;
        }
    } else {
        *value = (int64_t)parsed;
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

static CountStatus count_sequences(const int64_t *values,
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

    states[0].sum = INT64_C(0);
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

                if ((values[j] > 0 &&
                     states[i].sum > INT64_MAX - values[j]) ||
                    (values[j] < 0 &&
                     states[i].sum < INT64_MIN - values[j])) {
                    free(candidates);
                    free(states);
                    return COUNT_OVERFLOW;
                }

                next_sum = states[i].sum + values[j];

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
            if (printf("%" PRIu64 "\n", result) < 0) {
                fprintf(stderr, "Output error\n");
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;

        case COUNT_MEMORY_ERROR:
            fprintf(stderr, "Memory allocation failed\n");
            break;

        case COUNT_OVERFLOW:
            fprintf(stderr, "Numeric overflow\n");
            break;

        case COUNT_INVALID_ARGUMENT:
        default:
            fprintf(stderr, "Invalid argument\n");
            break;
    }

    return EXIT_FAILURE;
}