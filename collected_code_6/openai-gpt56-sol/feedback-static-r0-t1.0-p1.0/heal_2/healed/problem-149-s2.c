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

static size_t lower_bound_value(const Entry *entries, size_t count,
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

static size_t upper_bound_value(const Entry *entries, size_t count,
                                int64_t value)
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

    return low == first ? SIZE_MAX : entries[low - 1].index;
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
            predecessor = find_latest_predecessor(entries, count,
                                                  array[i] - 1, i);
        }

        if (array[i] < INT64_MAX) {
            size_t candidate = find_latest_predecessor(entries, count,
                                                       array[i] + 1, i);

            if (candidate != SIZE_MAX &&
                (predecessor == SIZE_MAX ||
                 lengths[candidate] > lengths[predecessor])) {
                predecessor = candidate;
            }
        }

        previous[i] = predecessor;
        lengths[i] = predecessor == SIZE_MAX ? 1 : lengths[predecessor] + 1;

        if (lengths[i] > best_length) {
            best_length = lengths[i];
            best_index = i;
        }
    }

    if (best_length > SIZE_MAX / sizeof(*sequence)) {
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
        sequence[position - 1] = array[best_index];
        best_index = previous[best_index];
    }

    free(entries);
    free(lengths);
    free(previous);

    *result = sequence;
    *result_count = best_length;
    return 0;
}

static int read_token(char **token)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 32;
    int c;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        c = fgetc(stdin);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return ferror(stdin) ? -1 : 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while (c != EOF && !isspace((unsigned char)c)) {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

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

        buffer[length++] = (char)c;
        c = fgetc(stdin);
    }

    if (c == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_size_value(size_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;
    int status;

    if (value == NULL) {
        return -1;
    }

    status = read_token(&buffer);
    if (status != 1) {
        free(buffer);
        return -1;
    }

    if (buffer[0] == '\0' || buffer[0] == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        free(buffer);
        return -1;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 0;
}

static int read_int64_value(int64_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    intmax_t parsed;
    int status;

    if (value == NULL) {
        return -1;
    }

    status = read_token(&buffer);
    if (status != 1) {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return -1;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 0;
}

int main(void)
{
    size_t count;
    int64_t *array = NULL;
    int64_t *sequence = NULL;
    size_t sequence_count = 0;

    if (read_size_value(&count) != 0 || count == 0 ||
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
        if (read_int64_value(&array[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (longest_adjacent_difference_one(array, count, &sequence,
                                        &sequence_count) != 0) {
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