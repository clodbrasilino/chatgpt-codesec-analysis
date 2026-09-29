#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int compare_tuples(const void *lhs, const void *rhs)
{
    const Tuple *a = lhs;
    const Tuple *b = rhs;

    if (a->first < b->first) {
        return -1;
    }
    if (a->first > b->first) {
        return 1;
    }
    if (a->second < b->second) {
        return -1;
    }
    if (a->second > b->second) {
        return 1;
    }
    return 0;
}

static int read_line(char **line, size_t *capacity)
{
    ssize_t length;

    if (line == NULL || capacity == NULL) {
        return -1;
    }

    errno = 0;
    length = getline(line, capacity, stdin);
    if (length < 0) {
        return -1;
    }

    if (length > 0 && (*line)[length - 1] == '\n') {
        (*line)[--length] = '\0';
    }

    if (length > 0 && (*line)[length - 1] == '\r') {
        (*line)[length - 1] = '\0';
    }

    return 0;
}

static void skip_horizontal_space(char **cursor)
{
    while (**cursor == ' ' || **cursor == '\t') {
        ++*cursor;
    }
}

static int read_size(size_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    char *cursor;
    char *end;
    uintmax_t parsed;
    int status = -1;

    if (value == NULL || read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    cursor = line;
    skip_horizontal_space(&cursor);

    if (*cursor == '-' || *cursor == '\0') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(cursor, &end, 10);

    if (end == cursor || errno == ERANGE || parsed > SIZE_MAX) {
        goto cleanup;
    }

    cursor = end;
    skip_horizontal_space(&cursor);

    if (*cursor != '\0') {
        goto cleanup;
    }

    *value = (size_t)parsed;
    status = 0;

cleanup:
    free(line);
    return status;
}

static int read_tuple(Tuple *tuple)
{
    char *line = NULL;
    size_t capacity = 0;
    char *cursor;
    char *end;
    intmax_t first;
    intmax_t second;
    int status = -1;

    if (tuple == NULL || read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    cursor = line;
    skip_horizontal_space(&cursor);

    errno = 0;
    first = strtoimax(cursor, &end, 10);
    if (end == cursor || errno == ERANGE ||
        first < INT64_MIN || first > INT64_MAX) {
        goto cleanup;
    }

    cursor = end;
    skip_horizontal_space(&cursor);

    errno = 0;
    second = strtoimax(cursor, &end, 10);
    if (end == cursor || errno == ERANGE ||
        second < INT64_MIN || second > INT64_MAX) {
        goto cleanup;
    }

    cursor = end;
    skip_horizontal_space(&cursor);

    if (*cursor != '\0') {
        goto cleanup;
    }

    tuple->first = (int64_t)first;
    tuple->second = (int64_t)second;
    status = 0;

cleanup:
    free(line);
    return status;
}

static size_t lower_bound_tuple(const Tuple *tuples, size_t count,
                                const Tuple *target)
{
    size_t left = 0;
    size_t right = count;

    while (left < right) {
        size_t middle = left + (right - left) / 2;

        if (compare_tuples(&tuples[middle], target) < 0) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return left;
}

static size_t upper_bound_tuple(const Tuple *tuples, size_t count,
                                const Tuple *target)
{
    size_t left = 0;
    size_t right = count;

    while (left < right) {
        size_t middle = left + (right - left) / 2;

        if (compare_tuples(&tuples[middle], target) <= 0) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return left;
}

static int add_product(uint64_t *total, uint64_t left, uint64_t right)
{
    uint64_t product;

    if (total == NULL) {
        return -1;
    }

    if (right != 0 && left > UINT64_MAX / right) {
        return -1;
    }

    product = left * right;

    if (*total > UINT64_MAX - product) {
        return -1;
    }

    *total += product;
    return 0;
}

static int count_bidirectional_pairs(Tuple *tuples, size_t count,
                                     uint64_t *result)
{
    uint64_t total = 0;
    size_t i = 0;

    if (result == NULL || (tuples == NULL && count != 0)) {
        return -1;
    }

    if (count > 1) {
        qsort(tuples, count, sizeof(*tuples), compare_tuples);
    }

    while (i < count) {
        size_t j = i + 1;
        size_t group_size;
        uint64_t occurrences;

        while (j < count &&
               compare_tuples(&tuples[i], &tuples[j]) == 0) {
            ++j;
        }

        group_size = j - i;
#if SIZE_MAX > UINT64_MAX
        if (group_size > UINT64_MAX) {
            return -1;
        }
#endif
        occurrences = (uint64_t)group_size;

        if (tuples[i].first == tuples[i].second) {
            if (occurrences > 1) {
                uint64_t left = occurrences;
                uint64_t right = occurrences - 1;

                if ((left & UINT64_C(1)) == 0) {
                    left /= 2;
                } else {
                    right /= 2;
                }

                if (add_product(&total, left, right) != 0) {
                    return -1;
                }
            }
        } else if (tuples[i].first < tuples[i].second) {
            Tuple reverse = {
                tuples[i].second,
                tuples[i].first
            };
            size_t start = lower_bound_tuple(tuples, count, &reverse);
            size_t end = upper_bound_tuple(tuples, count, &reverse);
            size_t reverse_size = end - start;
            uint64_t reverse_occurrences;

#if SIZE_MAX > UINT64_MAX
            if (reverse_size > UINT64_MAX) {
                return -1;
            }
#endif
            reverse_occurrences = (uint64_t)reverse_size;

            if (add_product(&total, occurrences,
                            reverse_occurrences) != 0) {
                return -1;
            }
        }

        i = j;
    }

    *result = total;
    return 0;
}

int main(void)
{
    size_t count;
    Tuple *tuples = NULL;
    uint64_t result;

    if (read_size(&count) != 0) {
        fputs("Invalid tuple count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Tuple count is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            fputs("Allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_tuple(&tuples[i]) != 0) {
            fputs("Invalid tuple input.\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (count_bidirectional_pairs(tuples, count, &result) != 0) {
        fputs("Unable to count pairs safely.\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Output failed.\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}