#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

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

static int read_line(char **line)
{
    char *buffer;
    size_t capacity = 128;
    size_t length = 0;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        size_t available;

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = required;
            } else {
                new_capacity = capacity * 2;
                if (new_capacity < required) {
                    new_capacity = required;
                }
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

        available = capacity - length;

        if (fgets(buffer + length,
                  /* Possible weaknesses found:
                   *  'INT_MAX' undeclared (first use in this function)
                   *  each undeclared identifier is reported only once for each function it appears in
                   *  use of undeclared identifier 'INT_MAX'
                   */
                  available > (size_t)INT_MAX ? INT_MAX : (int)available,
                  stdin) == NULL) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        {
            size_t added = 0;

            while (added < available - 1 &&
                   buffer[length + added] != '\0' &&
                   buffer[length + added] != '\n') {
                ++added;
            }

            length += added;

            if (buffer[length] == '\n') {
                break;
            }

            if (feof(stdin)) {
                break;
            }
        }
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
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

static int read_size(size_t *value)
{
    char *line = NULL;
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_line(&line)) {
        return 0;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed == 0 ||
        parsed > SIZE_MAX || !only_trailing_space(end)) {
        free(line);
        return 0;
    }

    *value = (size_t)parsed;
    free(line);
    return 1;
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_line(&line)) {
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

    if (start == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX ||
        !only_trailing_space(end)) {
        free(line);
        return 0;
    }

    *value = (int64_t)parsed;
    free(line);
    return 1;
}

static size_t find_longest_subsequence(const int64_t array[], size_t count,
                                       int64_t result[])
{
    Entry *entries;
    size_t *lengths;
    size_t *previous;
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

    if (!read_size(&count) ||
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