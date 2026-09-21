#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

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

static bool read_token(char **token)
{
    char *buffer = NULL;
    size_t capacity = 32;
    size_t length = 0;
    int ch;

    if (token == NULL) {
        return false;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            return false;
        }
    } while (isspace((unsigned char)ch));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return false;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                free(buffer);
                return false;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return false;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return false;
    }

    buffer[length] = '\0';
    *token = buffer;
    return true;
}

static bool read_size(size_t *value)
{
    char *token = NULL;
    char *end = NULL;
    uintmax_t parsed;
    bool valid;

    if (value == NULL || !read_token(&token)) {
        return false;
    }

    if (token[0] == '\0' || token[0] == '-' || token[0] == '+') {
        free(token);
        return false;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    valid = errno != ERANGE &&
            end != token &&
            *end == '\0' &&
            parsed <= SIZE_MAX;

    if (valid) {
        *value = (size_t)parsed;
    }

    free(token);
    return valid;
}

static bool read_int64(int64_t *value)
{
    char *token = NULL;
    char *end = NULL;
    intmax_t parsed;
    bool valid;

    if (value == NULL || !read_token(&token)) {
        return false;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    valid = errno != ERANGE &&
            end != token &&
            *end == '\0' &&
            parsed >= INT64_MIN &&
            parsed <= INT64_MAX;

    if (valid) {
        *value = (int64_t)parsed;
    }

    free(token);
    return valid;
}

static bool input_ended(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return false;
        }
    }

    return !ferror(stdin);
}

static size_t find_longest_subsequence(const int64_t array[], size_t count,
                                       int64_t result[])
{
    Entry *entries = NULL;
    size_t *lengths = NULL;
    size_t *previous = NULL;
    size_t best_length = 0;
    size_t best_index = 0;

    if (array == NULL || result == NULL || count == 0 ||
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
            int64_t target = array[i] - INT64_C(1);
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
        count > SIZE_MAX / sizeof(*array) ||
        count > SIZE_MAX / sizeof(*subsequence)) {
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

    if (!input_ended()) {
        free(array);
        free(subsequence);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
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