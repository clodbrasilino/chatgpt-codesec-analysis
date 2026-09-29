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

        while (next < count &&
               compare_tuples(&tuples[index], &tuples[next]) == 0) {
            ++next;
        }

        frequency = (uint64_t)(next - index);

        if (tuples[index].first == tuples[index].second) {
            uint64_t addend = 0;

            if (frequency > 1) {
                if ((frequency & UINT64_C(1)) == 0) {
                    addend = (frequency / 2) * (frequency - 1);
                } else {
                    addend = frequency * ((frequency - 1) / 2);
                }
            }

            if (addend > UINT64_MAX - total) {
                return -1;
            }

            total += addend;
        } else if (tuples[index].first < tuples[index].second) {
            Tuple reverse = {
                tuples[index].second,
                tuples[index].first
            };
            size_t first = lower_bound(tuples, count, reverse);
            size_t last = upper_bound(tuples, count, reverse);
            uint64_t reverse_frequency = (uint64_t)(last - first);
            uint64_t addend;

            if (reverse_frequency != 0 &&
                frequency > UINT64_MAX / reverse_frequency) {
                return -1;
            }

            addend = frequency * reverse_frequency;

            if (addend > UINT64_MAX - total) {
                return -1;
            }

            total += addend;
        }

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

    if (scanf("%zu", &count) != 1) {
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
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64 " %" SCNd64,
                  &tuples[i].first, &tuples[i].second) != 2) {
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