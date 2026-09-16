#include <stdio.h>
#include <stdlib.h>
/* Possible weaknesses found:
 *  'SCNd64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
 */
#include <stdint.h>

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
        int comparison = compare_tuples(&tuples[middle], &target);

        if (comparison < 0) {
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
        int comparison = compare_tuples(&tuples[middle], &target);

        if (comparison <= 0) {
            low = middle + 1;
        } else {
            high = middle;
        }
    }

    return low;
}

static int count_bidirectional_pairs(Tuple *tuples, size_t count, uint64_t *result)
{
    uint64_t total = 0;
    size_t index = 0;

    if (result == NULL || (count > 0 && tuples == NULL)) {
        return -1;
    }

    qsort(tuples, count, sizeof(*tuples), compare_tuples);

    while (index < count) {
        size_t next = index + 1;
        uint64_t frequency;
        Tuple reverse;

        while (next < count &&
               compare_tuples(&tuples[index], &tuples[next]) == 0) {
            ++next;
        }

        frequency = (uint64_t)(next - index);

        if (tuples[index].first == tuples[index].second) {
            if (frequency > 1) {
                uint64_t addend = frequency * (frequency - 1) / 2;
                if (UINT64_MAX - total < addend) {
                    return -1;
                }
                total += addend;
            }
        } else if (tuples[index].first < tuples[index].second) {
            size_t first;
            size_t last;
            uint64_t reverse_frequency;
            uint64_t addend;

            reverse.first = tuples[index].second;
            reverse.second = tuples[index].first;
            first = lower_bound(tuples, count, reverse);
            last = upper_bound(tuples, count, reverse);
            reverse_frequency = (uint64_t)(last - first);

            if (reverse_frequency != 0 &&
                frequency > UINT64_MAX / reverse_frequency) {
                return -1;
            }

            addend = frequency * reverse_frequency;
            if (UINT64_MAX - total < addend) {
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

    if (count > 0) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         *  expected ')'
         *  expected ')' before 'SCNd64'
         *  to match this '('
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

    /* Possible weaknesses found:
     *  expected ')'
     *  'PRIu64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
     *  expected ')' before 'PRIu64'
     *  to match this '('
     */
    if (printf("%" PRIu64 "\n", result) < 0) {
        fprintf(stderr, "Output failed\n");
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}