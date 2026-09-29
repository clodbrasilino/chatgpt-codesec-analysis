#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>

typedef struct {
    int64_t value;
    size_t index;
} Entry;

static int compare_entries(const void *left, const void *right)
{
    const Entry *a = left;
    const Entry *b = right;

    if (a->value < b->value) {
        return -1;
    }
    if (a->value > b->value) {
        return 1;
    }
    if (a->index < b->index) {
        return -1;
    }
    if (a->index > b->index) {
        return 1;
    }
    return 0;
}

static size_t lower_bound_value(const Entry entries[], size_t count,
                                int64_t value)
{
    size_t low = 0;
    size_t high = count;

    while (low < high) {
        size_t middle = low + (high - low) / 2;

        if (entries[middle].value < value) {
            low = middle + 1;
        } else {
            high = middle;
        }
    }

    return low;
}

static int read_token(char **token)
{
    enum {
        INITIAL_CAPACITY = 32,
        MAX_TOKEN_LENGTH = 1024
    };

    char *buffer;
    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0;
    int ch;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length >= MAX_TOKEN_LENGTH) {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF && !isspace((unsigned char)ch));

            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity = capacity * 2;
            char *new_buffer;

            if (new_capacity > MAX_TOKEN_LENGTH + 1) {
                new_capacity = MAX_TOKEN_LENGTH + 1;
            }

            if (new_capacity < required) {
                free(buffer);
                return 0;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        ch = fgetc(stdin);
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_size(size_t *value)
{
    char *token = NULL;
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    if (token[0] == '\0' || token[0] == '-' || token[0] == '+') {
        free(token);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > SIZE_MAX) {
        free(token);
        return 0;
    }

    *value = (size_t)parsed;
    free(token);
    return 1;
}

static int read_int64(int64_t *value)
{
    char *token = NULL;
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(token);
        return 0;
    }

    *value = (int64_t)parsed;
    free(token);
    return 1;
}

static size_t find_longest_subsequence(const int64_t array[], size_t count,
                                       int64_t result[])
{
    Entry *entries = NULL;
    size_t *lengths = NULL;
    size_t *previous = NULL;
    size_t best_length = 0;
    size_t best_index = 0;

    if (count == 0 || array == NULL || result == NULL ||
        count > SIZE_MAX / sizeof(*entries) ||
        count > SIZE_MAX / sizeof(*lengths) ||
        count > SIZE_MAX / sizeof(*previous)) {
        return 0;
    }

    entries = malloc(count * sizeof(*entries));
    lengths = malloc(count * sizeof(*lengths));
    previous = malloc(count * sizeof(*previous));

    if (entries == NULL || lengths == NULL || previous == NULL) {
        free(entries);
        free(lengths);
        free(previous);
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        entries[i].value = array[i];
        entries[i].index = i;
        lengths[i] = 1;
        previous[i] = SIZE_MAX;
    }

    qsort(entries, count, sizeof(*entries), compare_entries);

    for (size_t i = 0; i < count; ++i) {
        if (array[i] != INT64_MIN) {
            int64_t target = array[i] - 1;
            size_t position = lower_bound_value(entries, count, target);
            size_t candidate_length = 0;
            size_t candidate_index = SIZE_MAX;

            while (position < count && entries[position].value == target) {
                size_t index = entries[position].index;

                if (index >= i) {
                    break;
                }

                if (lengths[index] > candidate_length) {
                    candidate_length = lengths[index];
                    candidate_index = index;
                }

                ++position;
            }

            if (candidate_index != SIZE_MAX) {
                lengths[i] = candidate_length + 1;
                previous[i] = candidate_index;
            }
        }

        if (lengths[i] > best_length) {
            best_length = lengths[i];
            best_index = i;
        }
    }

    for (size_t i = best_length; i > 0; --i) {
        result[i - 1] = array[best_index];

        if (i > 1) {
            if (previous[best_index] == SIZE_MAX) {
                free(entries);
                free(lengths);
                free(previous);
                return 0;
            }

            best_index = previous[best_index];
        }
    }

    free(entries);
    free(lengths);
    free(previous);
    return best_length;
}

int main(void)
{
    size_t count;
    int64_t *array = NULL;
    int64_t *subsequence = NULL;
    size_t length;

    if (!read_size(&count) || count == 0 ||
        count > SIZE_MAX / sizeof(*array)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(count * sizeof(*array));
    subsequence = malloc(count * sizeof(*subsequence));

    if (array == NULL || subsequence == NULL) {
        free(array);
        free(subsequence);
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64(&array[i])) {
            free(array);
            free(subsequence);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    length = find_longest_subsequence(array, count, subsequence);

    if (length == 0) {
        free(array);
        free(subsequence);
        fputs("Unable to find subsequence\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", length) < 0) {
        free(array);
        free(subsequence);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (printf("%" PRId64 "%c", subsequence[i],
                   i + 1 == length ? '\n' : ' ') < 0) {
            free(array);
            free(subsequence);
            return EXIT_FAILURE;
        }
    }

    free(array);
    free(subsequence);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}