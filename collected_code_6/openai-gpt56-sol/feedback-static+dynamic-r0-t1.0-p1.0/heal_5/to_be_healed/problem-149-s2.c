#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

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

static size_t lower_bound_value(const Entry *entries, size_t count, int64_t value)
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

static size_t upper_bound_value(const Entry *entries, size_t count, int64_t value)
{
    size_t low = 0;
    size_t high = count;

    while (low < high) {
        size_t middle = low + (high - low) / 2;

        if (entries[middle].value <= value) {
            low = middle + 1;
        } else {
            high = middle;
        }
    }

    return low;
}

static size_t find_latest_predecessor(const Entry *entries, size_t count,
                                      int64_t value, size_t current_index)
{
    size_t first = lower_bound_value(entries, count, value);
    size_t last = upper_bound_value(entries, count, value);
    size_t low = first;
    size_t high = last;

    while (low < high) {
        size_t middle = low + (high - low) / 2;

        if (entries[middle].index < current_index) {
            low = middle + 1;
        } else {
            high = middle;
        }
    }

    if (low == first) {
        return SIZE_MAX;
    }

    return entries[low - 1].index;
}

static int read_token(char **token)
{
    size_t length = 0;
    size_t capacity = 32;
    int ch;
    char *buffer;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF) {
            return -1;
        }

        if (!isspace((unsigned char)ch)) {
            break;
        }
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (isspace((unsigned char)ch)) {
            break;
        }
    }

    buffer[length] = '\0';
    *token = buffer;
    return 0;
}

static int read_size(size_t *value)
{
    char *token = NULL;
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || read_token(&token) != 0) {
        return -1;
    }

    if (token[0] == '\0' || token[0] == '-' || token[0] == '+') {
        free(token);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (end == token || *end != '\0' || errno == ERANGE ||
        parsed > (uintmax_t)SIZE_MAX) {
        free(token);
        return -1;
    }

    *value = (size_t)parsed;
    free(token);
    return 0;
}

static int read_int64(int64_t *value)
{
    char *token = NULL;
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || read_token(&token) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (end == token || *end != '\0' || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(token);
        return -1;
    }

    *value = (int64_t)parsed;
    free(token);
    return 0;
}

static int input_has_extra_tokens(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 1;
        }
    }

    return ferror(stdin) != 0;
}

static int longest_adjacent_difference_one(const int64_t *array, size_t count,
                                           int64_t **result,
                                           size_t *result_count)
{
    Entry *entries = NULL;
    size_t *lengths = NULL;
    size_t *previous = NULL;
    int64_t *sequence = NULL;
    size_t best_length = 0;
    size_t best_index = SIZE_MAX;

    if (array == NULL || result == NULL || result_count == NULL || count == 0) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (count > SIZE_MAX / sizeof(*entries) ||
        count > SIZE_MAX / sizeof(*lengths) ||
        count > SIZE_MAX / sizeof(*previous)) {
        return -1;
    }

    entries = malloc(count * sizeof(*entries));
    lengths = malloc(count * sizeof(*lengths));
    previous = malloc(count * sizeof(*previous));

    if (entries == NULL || lengths == NULL || previous == NULL) {
        free(entries);
        free(lengths);
        free(previous);
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        entries[i].value = array[i];
        entries[i].index = i;
    }

    qsort(entries, count, sizeof(*entries), compare_entries);

    for (size_t i = 0; i < count; ++i) {
        size_t predecessor = SIZE_MAX;

        if (array[i] > INT64_MIN) {
            predecessor = find_latest_predecessor(
                entries, count, array[i] - INT64_C(1), i);
        }

        if (array[i] < INT64_MAX) {
            size_t candidate = find_latest_predecessor(
                entries, count, array[i] + INT64_C(1), i);

            if (candidate != SIZE_MAX) {
                if (predecessor == SIZE_MAX ||
                    lengths[candidate] > lengths[predecessor] ||
                    /* Possible weaknesses found:
                     *  Array index 'predecessor' is used before limits check. [arrayIndexThenCheck]
                     */
                    (lengths[candidate] == lengths[predecessor] &&
                     candidate > predecessor)) {
                    predecessor = candidate;
                }
            }
        }

        previous[i] = predecessor;

        if (predecessor == SIZE_MAX) {
            lengths[i] = 1;
        } else {
            if (predecessor >= i || lengths[predecessor] == SIZE_MAX) {
                free(entries);
                free(lengths);
                free(previous);
                return -1;
            }
            lengths[i] = lengths[predecessor] + 1;
        }

        if (lengths[i] > best_length) {
            best_length = lengths[i];
            best_index = i;
        }
    }

    if (best_length == 0 || best_length > SIZE_MAX / sizeof(*sequence)) {
        free(entries);
        free(lengths);
        free(previous);
        return -1;
    }

    sequence = malloc(best_length * sizeof(*sequence));
    if (sequence == NULL) {
        free(entries);
        free(lengths);
        free(previous);
        return -1;
    }

    for (size_t position = best_length; position > 0; --position) {
        if (best_index == SIZE_MAX || best_index >= count) {
            free(sequence);
            free(entries);
            free(lengths);
            free(previous);
            return -1;
        }

        sequence[position - 1] = array[best_index];
        best_index = previous[best_index];
    }

    if (best_index != SIZE_MAX) {
        free(sequence);
        free(entries);
        free(lengths);
        free(previous);
        return -1;
    }

    free(entries);
    free(lengths);
    free(previous);

    *result = sequence;
    *result_count = best_length;
    return 0;
}

int main(void)
{
    size_t count;
    int64_t *array = NULL;
    int64_t *sequence = NULL;
    size_t sequence_count = 0;

    if (read_size(&count) != 0 || count == 0 ||
        count > SIZE_MAX / sizeof(*array)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(count * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64(&array[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (input_has_extra_tokens()) {
        fputs("Invalid input\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    if (longest_adjacent_difference_one(
            array, count, &sequence, &sequence_count) != 0) {
        fputs("Unable to find subsequence\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", sequence_count) < 0) {
        free(sequence);
        free(array);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < sequence_count; ++i) {
        if (printf("%" PRId64 "%c", sequence[i],
                   i + 1 == sequence_count ? '\n' : ' ') < 0) {
            free(sequence);
            free(array);
            return EXIT_FAILURE;
        }
    }

    free(sequence);
    free(array);
    return EXIT_SUCCESS;
}