#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int compare_uint64(const void *left, const void *right)
{
    const uint64_t a = *(const uint64_t *)left;
    const uint64_t b = *(const uint64_t *)right;

    return (a > b) - (a < b);
}

static int read_uintmax(uintmax_t maximum, uintmax_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length == SIZE_MAX - 1) {
            free(line);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(line);
                    return 0;
                }
                new_capacity = capacity * 2;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return 0;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    if (character == EOF && length == 0) {
        free(line);
        return 0;
    }

    if (length + 1 > capacity) {
        char *new_line = realloc(line, length + 1);
        if (new_line == NULL) {
            free(line);
            return 0;
        }
        line = new_line;
    }

    line[length] = '\0';

    errno = 0;
    parsed = strtoumax(line, &end, 10);

    if (errno != 0 || end == line || parsed == 0 || parsed > maximum) {
        free(line);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = parsed;
    free(line);
    return 1;
}

static int read_size(size_t *value)
{
    uintmax_t parsed;

    if (value == NULL || !read_uintmax(SIZE_MAX, &parsed)) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed;

    if (value == NULL || !read_uintmax(UINT64_MAX, &parsed)) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int largest_divisible_subset(const uint64_t *values,
                                    size_t count,
                                    uint64_t **subset,
                                    size_t *subset_count)
{
    uint64_t *sorted = NULL;
    size_t *lengths = NULL;
    size_t *previous = NULL;
    uint64_t *result = NULL;
    size_t best_index = 0;
    size_t best_length = 0;

    if (values == NULL || subset == NULL || subset_count == NULL || count == 0) {
        return 0;
    }

    *subset = NULL;
    *subset_count = 0;

    if (count > SIZE_MAX / sizeof(*sorted) ||
        count > SIZE_MAX / sizeof(*lengths) ||
        count > SIZE_MAX / sizeof(*previous)) {
        return 0;
    }

    sorted = malloc(count * sizeof(*sorted));
    lengths = malloc(count * sizeof(*lengths));
    previous = malloc(count * sizeof(*previous));

    if (sorted == NULL || lengths == NULL || previous == NULL) {
        free(sorted);
        free(lengths);
        free(previous);
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (values[i] == 0) {
            free(sorted);
            free(lengths);
            free(previous);
            return 0;
        }
        sorted[i] = values[i];
    }

    qsort(sorted, count, sizeof(*sorted), compare_uint64);

    for (size_t i = 0; i < count; ++i) {
        lengths[i] = 1;
        previous[i] = SIZE_MAX;

        for (size_t j = 0; j < i; ++j) {
            if (sorted[i] % sorted[j] == 0 &&
                lengths[j] < SIZE_MAX &&
                lengths[j] + 1 > lengths[i]) {
                lengths[i] = lengths[j] + 1;
                previous[i] = j;
            }
        }

        if (lengths[i] > best_length) {
            best_length = lengths[i];
            best_index = i;
        }
    }

    if (best_length == 0 || best_length > SIZE_MAX / sizeof(*result)) {
        free(sorted);
        free(lengths);
        free(previous);
        return 0;
    }

    result = malloc(best_length * sizeof(*result));
    if (result == NULL) {
        free(sorted);
        free(lengths);
        free(previous);
        return 0;
    }

    {
        size_t index = best_index;

        for (size_t position = best_length; position > 0; --position) {
            result[position - 1] = sorted[index];

            if (position > 1) {
                if (previous[index] == SIZE_MAX ||
                    previous[index] >= index ||
                    previous[index] >= count) {
                    free(result);
                    free(sorted);
                    free(lengths);
                    free(previous);
                    return 0;
                }
                index = previous[index];
            }
        }
    }

    free(sorted);
    free(lengths);
    free(previous);

    *subset = result;
    *subset_count = best_length;
    return 1;
}

int main(void)
{
    size_t count;
    uint64_t *values = NULL;
    uint64_t *subset = NULL;
    size_t subset_count = 0;

    if (!read_size(&count) || count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Invalid element count.\n");
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_uint64(&values[i])) {
            fprintf(stderr, "Invalid positive integer.\n");
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!largest_divisible_subset(values, count, &subset, &subset_count)) {
        fprintf(stderr, "Unable to find the subset.\n");
        free(values);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < subset_count; ++i) {
        printf("%" PRIu64 "%c",
               subset[i],
               i + 1 == subset_count ? '\n' : ' ');
    }

    free(subset);
    free(values);
    return EXIT_SUCCESS;
}