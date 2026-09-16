#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

typedef struct {
    int first;
    int second;
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

static uint64_t count_bidirectional_pairs(Tuple *tuples, size_t count)
{
    uint64_t result = 0;
    size_t i = 0;

    if (tuples == NULL || count < 2) {
        return 0;
    }

    qsort(tuples, count, sizeof(*tuples), compare_tuples);

    while (i < count) {
        size_t j = i + 1;
        size_t reverse_start;
        size_t reverse_end;

        while (j < count &&
               tuples[j].first == tuples[i].first &&
               tuples[j].second == tuples[i].second) {
            ++j;
        }

        if (tuples[i].first == tuples[i].second) {
            uint64_t occurrences = (uint64_t)(j - i);
            result += occurrences * (occurrences - 1U) / 2U;
        } else if (tuples[i].first < tuples[i].second) {
            Tuple reverse = {tuples[i].second, tuples[i].first};
            Tuple *found = bsearch(
                &reverse, tuples, count, sizeof(*tuples), compare_tuples
            );

            if (found != NULL) {
                reverse_start = (size_t)(found - tuples);
                reverse_end = reverse_start + 1;

                while (reverse_start > 0 &&
                       tuples[reverse_start - 1].first == reverse.first &&
                       tuples[reverse_start - 1].second == reverse.second) {
                    --reverse_start;
                }

                while (reverse_end < count &&
                       tuples[reverse_end].first == reverse.first &&
                       tuples[reverse_end].second == reverse.second) {
                    ++reverse_end;
                }

                result += (uint64_t)(j - i) *
                          (uint64_t)(reverse_end - reverse_start);
            }
        }

        i = j;
    }

    return result;
}

int main(void)
{
    size_t count;
    Tuple *tuples = NULL;
    uint64_t result;
    int scan_result;

    scan_result = scanf("%zu", &count);
    if (scan_result != 1) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Tuple count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > 0) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        scan_result = scanf("%d %d", &tuples[i].first, &tuples[i].second);
        if (scan_result != 2) {
            fputs("Invalid tuple input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    result = count_bidirectional_pairs(tuples, count);
    printf("%" PRIu64 "\n", result);

    if (ferror(stdout) != 0) {
        fputs("Output error\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}