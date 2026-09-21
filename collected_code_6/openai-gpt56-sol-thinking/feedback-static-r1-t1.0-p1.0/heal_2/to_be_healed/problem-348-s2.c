#include <ctype.h>
#include <errno.h>
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

static int read_token(char *buffer, size_t capacity)
{
    size_t length = 0;
    int character;
    int too_long = 0;

    if (buffer == NULL || capacity < 2) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
        if (character == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)character));

    do {
        if (length + 1 < capacity) {
            buffer[length++] = (char)character;
        } else {
            too_long = 1;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    } while (character != EOF && !isspace((unsigned char)character));

    if (too_long) {
        return -1;
    }

    buffer[length] = '\0';
    return 1;
}

static int read_size_value(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *end;
    uintmax_t parsed;
    int status;

    if (value == NULL) {
        return 0;
    }

    status = read_token(buffer, sizeof(buffer));
    if (status != 1 || buffer[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64_value(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *end;
    intmax_t parsed;
    int status;

    if (value == NULL) {
        return 0;
    }

    status = read_token(buffer, sizeof(buffer));
    if (status != 1) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
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

CountStatus count_sequences(const int64_t *values,
                            size_t value_count,
                            size_t sequence_length,
                            uint64_t *result)
{
    State *states;
    size_t state_count;
    size_t position;

    if (result == NULL || (values == NULL && value_count != 0)) {
        return COUNT_INVALID_ARGUMENT;
    }

    *result = 0;

    states = malloc(sizeof(*states));
    if (states == NULL) {
        return COUNT_MEMORY_ERROR;
    }

    states[0].sum = 0;
    states[0].count = 1;
    state_count = 1;

    for (position = 0; position < sequence_length; ++position) {
        State *candidates;
        size_t capacity;
        size_t candidate_count = 0;
        size_t merged_count = 0;
        size_t i;
        size_t j;

        if (value_count == 0) {
            free(states);
            return COUNT_SUCCESS;
        }

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

        qsort(candidates, candidate_count, sizeof(*candidates),
              compare_states);

        for (i = 0; i < candidate_count; ++i) {
            if (merged_count > 0 &&
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
    int64_t *values = NULL;
    size_t value_count;
    size_t sequence_length;
    size_t i;
    uint64_t result;
    CountStatus status;

    if (!read_size_value(&value_count) ||
        !read_size_value(&sequence_length)) {
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
        if (!read_int64_value(&values[i])) {
            fprintf(stderr, "Invalid input\n");
            free(values);
            return EXIT_FAILURE;
        }
    }

    status = count_sequences(values, value_count, sequence_length, &result);
    free(values);

    switch (status) {
        case COUNT_SUCCESS:
            printf("%" PRIu64 "\n", result);
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