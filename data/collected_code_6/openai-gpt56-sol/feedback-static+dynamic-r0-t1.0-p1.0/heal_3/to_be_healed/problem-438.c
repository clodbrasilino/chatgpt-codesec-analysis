#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;

    if (a->first != b->first) {
        return a->first < b->first ? -1 : 1;
    }

    if (a->second != b->second) {
        return a->second < b->second ? -1 : 1;
    }

    return 0;
}

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || parsed > SIZE_MAX) {
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
    char buffer[256];
    char *cursor;
    char *end;
    intmax_t first;
    intmax_t second;

    if (tuple == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    cursor = buffer;

    errno = 0;
    first = strtoimax(cursor, &end, 10);
    if (errno == ERANGE || end == cursor ||
        first < INT64_MIN || first > INT64_MAX) {
        return -1;
    }

    cursor = end;
    errno = 0;
    second = strtoimax(cursor, &end, 10);
    if (errno == ERANGE || end == cursor ||
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

static size_t lower_bound(const Tuple *tuples, size_t count, Tuple target)
{
    size_t low = 0;
    size_t high = count;

    while (low < high) {
        size_t middle = low + (high - low) / 2;

        if (compare_tuples(&tuples[middle], &target) < 0) {
            low = middle + 1;
        } else {
            high = middle;
        }
    }

    return low;
}

static size_t upper_bound(const Tuple *tuples, size_t count, Tuple target)
{
    size_t low = 0;
    size_t high = count;

    while (low < high) {
        size_t middle = low + (high - low) / 2;

        if (compare_tuples(&tuples[middle], &target) <= 0) {
            low = middle + 1;
        } else {
            high = middle;
        }
    }

    return low;
}

static int checked_choose_two(uint64_t value, uint64_t *result)
{
    uint64_t a = value;
    uint64_t b = value - 1;

    if ((a & 1U) == 0) {
        a /= 2;
    } else {
        b /= 2;
    }

    if (b != 0 && a > UINT64_MAX / b) {
        return -1;
    }

    *result = a * b;
    return 0;
}

static int count_bidirectional_pairs(Tuple *tuples, size_t count,
                                     uint64_t *result)
{
    uint64_t total = 0;
    size_t index = 0;

    if (result == NULL || (count != 0 && tuples == NULL)) {
        return -1;
    }

    if (count > 1) {
        qsort(tuples, count, sizeof(*tuples), compare_tuples);
    }

    while (index < count) {
        size_t next = index + 1;
        uint64_t frequency;
        uint64_t addend = 0;

        while (next < count &&
               compare_tuples(&tuples[index], &tuples[next]) == 0) {
            ++next;
        }

        if (next - index > UINT64_MAX) {
            return -1;
        }

        frequency = (uint64_t)(next - index);

        if (tuples[index].first == tuples[index].second) {
            if (checked_choose_two(frequency, &addend) != 0) {
                return -1;
            }
        } else if (tuples[index].first < tuples[index].second) {
            Tuple reverse = {
                tuples[index].second,
                tuples[index].first
            };
            size_t first = lower_bound(tuples, count, reverse);
            size_t last = upper_bound(tuples, count, reverse);
            size_t reverse_count = last - first;
            uint64_t reverse_frequency;

            if (reverse_count > UINT64_MAX) {
                return -1;
            }

            reverse_frequency = (uint64_t)reverse_count;

            if (reverse_frequency != 0 &&
                frequency > UINT64_MAX / reverse_frequency) {
                return -1;
            }

            addend = frequency * reverse_frequency;
        }

        if (addend > UINT64_MAX - total) {
            return -1;
        }

        total += addend;
        index = next;
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
        fprintf(stderr, "Invalid tuple count\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fprintf(stderr, "Tuple count is too large\n");
        return EXIT_FAILURE;
    }

    if (count != 0) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_tuple(&tuples[i]) != 0) {
            fprintf(stderr, "Invalid tuple input\n");
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (count_bidirectional_pairs(tuples, count, &result) != 0) {
        fprintf(stderr, "Unable to count pairs\n");
        free(tuples);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fprintf(stderr, "Output failed\n");
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}