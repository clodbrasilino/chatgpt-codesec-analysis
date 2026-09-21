#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
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

static size_t lower_bound_value(const Entry entries[], size_t count, int64_t value)
{
    size_t low = 0;
    size_t high = count;

    while (low < high) {
        size_t middle = low + (high - low) / 2U;

        if (entries[middle].value < value) {
            low = middle + 1U;
        } else {
            high = middle;
        }
    }

    return low;
}

static int read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0U;

    if (buffer == NULL || capacity < 2U) {
        return 0;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1U >= capacity) {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF && !isspace((unsigned char)ch));
            return 0;
        }

        buffer[length++] = (char)ch;
        ch = fgetc(stdin);
    }

    buffer[length] = '\0';
    return 1;
}

static int read_size(size_t *value)
{
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer)) ||
        buffer[0] == '-' || buffer[0] == '+') {
        return 0;
    }

    parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || *end != '\0' || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    char buffer[128];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer))) {
        return 0;
    }

    parsed = strtoimax(buffer, &end, 10);

    if (end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static size_t find_longest_subsequence(const int64_t array[], size_t count,
                                       int64_t result[])
{
    Entry *entries;
    size_t *lengths;
    size_t *previous;
    size_t best_length = 0U;
    size_t best_index = 0U;

    if (count == 0U || array == NULL || result == NULL ||
        count > SIZE_MAX / sizeof(*entries) ||
        count > SIZE_MAX / sizeof(*lengths) ||
        count > SIZE_MAX / sizeof(*previous)) {
        return 0U;
    }

    entries = malloc(count * sizeof(*entries));
    lengths = malloc(count * sizeof(*lengths));
    previous = malloc(count * sizeof(*previous));

    if (entries == NULL || lengths == NULL || previous == NULL) {
        free(entries);
        free(lengths);
        free(previous);
        return 0U;
    }

    for (size_t i = 0U; i < count; ++i) {
        entries[i].value = array[i];
        entries[i].index = i;
        lengths[i] = 1U;
        previous[i] = SIZE_MAX;
    }

    qsort(entries, count, sizeof(*entries), compare_entries);

    for (size_t i = 0U; i < count; ++i) {
        if (array[i] != INT64_MIN) {
            int64_t target = array[i] - 1;
            size_t position = lower_bound_value(entries, count, target);
            size_t candidate_length = 0U;
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
                lengths[i] = candidate_length + 1U;
                previous[i] = candidate_index;
            }
        }

        if (lengths[i] > best_length) {
            best_length = lengths[i];
            best_index = i;
        }
    }

    for (size_t i = best_length; i > 0U; --i) {
        result[i - 1U] = array[best_index];

        if (previous[best_index] != SIZE_MAX) {
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
    int64_t *array;
    int64_t *subsequence;
    size_t length;

    if (!read_size(&count) || count == 0U ||
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

    for (size_t i = 0U; i < count; ++i) {
        if (!read_int64(&array[i])) {
            free(array);
            free(subsequence);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    length = find_longest_subsequence(array, count, subsequence);

    if (length == 0U) {
        free(array);
        free(subsequence);
        fputs("Unable to find subsequence\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", length);

    for (size_t i = 0U; i < length; ++i) {
        printf("%" PRId64 "%c", subsequence[i],
               i + 1U == length ? '\n' : ' ');
    }

    free(array);
    free(subsequence);

    return EXIT_SUCCESS;
}