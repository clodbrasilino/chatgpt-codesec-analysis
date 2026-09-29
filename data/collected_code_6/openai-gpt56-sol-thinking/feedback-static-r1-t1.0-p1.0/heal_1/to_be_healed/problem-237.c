#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

typedef enum {
    CHECK_ERROR = -1,
    CHECK_NOT_EQUAL = 0,
    CHECK_EQUAL = 1
} CheckResult;

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;

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

static int tuples_are_equal(const Tuple *a, const Tuple *b)
{
    return a->first == b->first && a->second == b->second;
}

static CheckResult records_have_equal_occurrences(const Tuple *tuples,
                                                  size_t count)
{
    Tuple *sorted;
    size_t index;
    size_t expected_frequency = 0;

    if (count == 0) {
        return CHECK_EQUAL;
    }

    if (tuples == NULL || count > SIZE_MAX / sizeof(*sorted)) {
        return CHECK_ERROR;
    }

    sorted = malloc(count * sizeof(*sorted));
    if (sorted == NULL) {
        return CHECK_ERROR;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted, tuples, count * sizeof(*sorted));
    qsort(sorted, count, sizeof(*sorted), compare_tuples);

    index = 0;
    while (index < count) {
        size_t end = index + 1;
        size_t frequency;

        while (end < count && tuples_are_equal(&sorted[index], &sorted[end])) {
            ++end;
        }

        frequency = end - index;

        if (expected_frequency == 0) {
            expected_frequency = frequency;
        } else if (frequency != expected_frequency) {
            free(sorted);
            return CHECK_NOT_EQUAL;
        }

        index = end;
    }

    free(sorted);
    return CHECK_EQUAL;
}

int main(void)
{
    Tuple *tuples = NULL;
    size_t count;
    size_t index;
    CheckResult result;

    if (scanf("%zu", &count) != 1) {
        fprintf(stderr, "Failed to read the tuple count.\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fprintf(stderr, "Tuple count is too large.\n");
        return EXIT_FAILURE;
    }

    if (count > 0) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            fprintf(stderr, "Failed to allocate memory.\n");
            return EXIT_FAILURE;
        }
    }

    for (index = 0; index < count; ++index) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64 " %" SCNd64,
                  &tuples[index].first,
                  &tuples[index].second) != 2) {
            fprintf(stderr, "Failed to read tuple %zu.\n", index + 1);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    result = records_have_equal_occurrences(tuples, count);
    free(tuples);

    if (result == CHECK_ERROR) {
        fprintf(stderr, "Unable to check record occurrences.\n");
        return EXIT_FAILURE;
    }

    puts(result == CHECK_EQUAL ? "YES" : "NO");
    return EXIT_SUCCESS;
}