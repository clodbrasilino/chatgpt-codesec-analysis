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

static int compare_states(const void *lhs, const void *rhs)
{
    const State *a = lhs;
    const State *b = rhs;

    return (a->sum > b->sum) - (a->sum < b->sum);
}

static int add_checked_i64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int add_checked_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || a > UINT64_MAX - b) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int read_line(FILE *stream, char **line, size_t *capacity)
{
    size_t length = 0;

    if (stream == NULL || line == NULL || capacity == NULL) {
        return 0;
    }

    if (*line == NULL) {
        *capacity = 64;
        *line = malloc(*capacity);
        if (*line == NULL) {
            *capacity = 0;
            return 0;
        }
    } else if (*capacity == 0) {
        return 0;
    }

    for (;;) {
        int ch;

        if (length + 1 >= *capacity) {
            size_t required;
            size_t new_capacity;
            char *resized;

            if (length > SIZE_MAX - 2) {
                return 0;
            }

            required = length + 2;
            new_capacity = *capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            if (new_capacity < required) {
                return 0;
            }

            resized = realloc(*line, new_capacity);
            if (resized == NULL) {
                return 0;
            }

            *line = resized;
            *capacity = new_capacity;
        }

        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                return 0;
            }
            break;
        }

        (*line)[length++] = (char)ch;

        if (ch == '\n') {
            break;
        }
    }

    (*line)[length] = '\0';
    return 1;
}

static int only_trailing_space(const char *text)
{
    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        if (!isspace((unsigned char)*text)) {
            return 0;
        }
        ++text;
    }

    return 1;
}

static int read_size(FILE *stream, size_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    char *start;
    char *end;
    uintmax_t parsed;
    int valid = 0;

    if (value == NULL || !read_line(stream, &line, &capacity)) {
        free(line);
        return 0;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end != start &&
        errno != ERANGE &&
        parsed <= SIZE_MAX &&
        only_trailing_space(end)) {
        *value = (size_t)parsed;
        valid = 1;
    }

    free(line);
    return valid;
}

static int read_i64(FILE *stream, int64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    char *start;
    char *end;
    intmax_t parsed;
    int valid = 0;

    if (value == NULL || !read_line(stream, &line, &capacity)) {
        free(line);
        return 0;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (end != start &&
        errno != ERANGE &&
        parsed >= INT64_MIN &&
        parsed <= INT64_MAX &&
        only_trailing_space(end)) {
        *value = (int64_t)parsed;
        valid = 1;
    }

    free(line);
    return valid;
}

static int count_sequences(const int64_t *values, size_t value_count,
                           size_t length, uint64_t *result)
{
    State *states;
    size_t state_count = 1;

    if (result == NULL || (value_count != 0 && values == NULL)) {
        return EINVAL;
    }

    states = malloc(sizeof(*states));
    if (states == NULL) {
        return ENOMEM;
    }

    states[0].sum = 0;
    states[0].count = 1;

    for (size_t position = 0; position < length; ++position) {
        size_t candidate_count;
        State *candidates;
        size_t used = 0;
        size_t merged = 0;

        if (value_count != 0 && state_count > SIZE_MAX / value_count) {
            free(states);
            return EOVERFLOW;
        }

        candidate_count = state_count * value_count;

        if (candidate_count > SIZE_MAX / sizeof(*candidates)) {
            free(states);
            return EOVERFLOW;
        }

        candidates = candidate_count == 0
                         ? NULL
                         : malloc(candidate_count * sizeof(*candidates));

        if (candidate_count != 0 && candidates == NULL) {
            free(states);
            return ENOMEM;
        }

        for (size_t i = 0; i < state_count; ++i) {
            for (size_t j = 0; j < value_count; ++j) {
                int64_t next_sum;

                if (!add_checked_i64(states[i].sum, values[j], &next_sum)) {
                    free(candidates);
                    free(states);
                    return EOVERFLOW;
                }

                if (next_sum >= 0) {
                    if (used == candidate_count) {
                        free(candidates);
                        free(states);
                        return EOVERFLOW;
                    }

                    candidates[used].sum = next_sum;
                    candidates[used].count = states[i].count;
                    ++used;
                }
            }
        }

        free(states);
        states = NULL;

        if (used == 0) {
            free(candidates);
            *result = 0;
            return 0;
        }

        qsort(candidates, used, sizeof(*candidates), compare_states);

        for (size_t i = 0; i < used; ++i) {
            if (merged > 0 &&
                candidates[merged - 1].sum == candidates[i].sum) {
                uint64_t total;

                if (!add_checked_u64(candidates[merged - 1].count,
                                     candidates[i].count, &total)) {
                    free(candidates);
                    return EOVERFLOW;
                }

                candidates[merged - 1].count = total;
            } else {
                candidates[merged++] = candidates[i];
            }
        }

        states = candidates;
        state_count = merged;
    }

    {
        uint64_t total = 0;

        for (size_t i = 0; i < state_count; ++i) {
            if (!add_checked_u64(total, states[i].count, &total)) {
                free(states);
                return EOVERFLOW;
            }
        }

        free(states);
        *result = total;
    }

    return 0;
}

int main(void)
{
    size_t value_count;
    size_t length;
    int64_t *values = NULL;
    uint64_t answer;
    int status;

    if (!read_size(stdin, &value_count) ||
        !read_size(stdin, &length)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (value_count > SIZE_MAX / sizeof(*values)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (value_count != 0) {
        values = malloc(value_count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < value_count; ++i) {
        if (!read_i64(stdin, &values[i])) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    status = count_sequences(values, value_count, length, &answer);
    free(values);

    if (status != 0) {
        const char *message;

        if (status == ENOMEM) {
            message = "out of memory";
        } else if (status == EOVERFLOW) {
            message = "numeric overflow";
        } else {
            message = "invalid argument";
        }

        fprintf(stderr, "Unable to count sequences: %s\n", message);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", answer);
    return EXIT_SUCCESS;
}