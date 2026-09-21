#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int compare_tuples(const void *lhs, const void *rhs)
{
    const Tuple *a = lhs;
    const Tuple *b = rhs;

    if (a->first != b->first) {
        return (a->first > b->first) - (a->first < b->first);
    }

    return (a->second > b->second) - (a->second < b->second);
}

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || fgets(line, sizeof(line), stdin) == NULL) {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || parsed > SIZE_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_tuple(Tuple *tuple)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[256];
    char *cursor;
    char *end;
    intmax_t first;
    intmax_t second;

    if (tuple == NULL || fgets(line, sizeof(line), stdin) == NULL) {
        return -1;
    }

    cursor = line;

    errno = 0;
    end = NULL;
    first = strtoimax(cursor, &end, 10);

    if (end == cursor || errno == ERANGE ||
        first < INT64_MIN || first > INT64_MAX) {
        return -1;
    }

    cursor = end;
    errno = 0;
    second = strtoimax(cursor, &end, 10);

    if (end == cursor || errno == ERANGE ||
        second < INT64_MIN || second > INT64_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return -1;
    }

    tuple->first = (int64_t)first;
    tuple->second = (int64_t)second;
    return 0;
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
        uint64_t occurrences;

        while (j < count && compare_tuples(&tuples[i], &tuples[j]) == 0) {
            ++j;
        }

        if (j - i > UINT64_MAX) {
            return -1;
        }

        occurrences = (uint64_t)(j - i);

        if (tuples[i].first == tuples[i].second) {
            if (occurrences > 1) {
                uint64_t a = occurrences;
                uint64_t b = occurrences - 1;

                if ((a & 1U) == 0) {
                    a /= 2;
                } else {
                    b /= 2;
                }

                if (add_product(&total, a, b) != 0) {
                    return -1;
                }
            }
        } else if (tuples[i].first < tuples[i].second) {
            Tuple reverse;
            size_t start;
            size_t end;
            uint64_t reverse_occurrences;

            reverse.first = tuples[i].second;
            reverse.second = tuples[i].first;

            start = lower_bound_tuple(tuples, count, &reverse);
            end = upper_bound_tuple(tuples, count, &reverse);

            if (end - start > UINT64_MAX) {
                return -1;
            }

            reverse_occurrences = (uint64_t)(end - start);

            if (add_product(&total, occurrences, reverse_occurrences) != 0) {
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