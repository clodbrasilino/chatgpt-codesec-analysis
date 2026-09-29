#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'strerror' is defined in header '<string.h>'; this is probably fixable by adding '#include <string.h>'
  */

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

static int count_bidirectional_pairs(Tuple *tuples, size_t count, uint64_t *result)
{
    uint64_t total = 0;
    size_t i = 0;

    if (tuples == NULL || result == NULL) {
        return -1;
    }

    if (count > 1) {
        qsort(tuples, count, sizeof(*tuples), compare_tuples);
    }

    while (i < count) {
        size_t j = i + 1;
        uint64_t occurrences;

        while (j < count &&
               tuples[j].first == tuples[i].first &&
               tuples[j].second == tuples[i].second) {
            ++j;
        }

        occurrences = (uint64_t)(j - i);

        if (tuples[i].first == tuples[i].second) {
            if (occurrences > 1) {
                uint64_t contribution;

                if (occurrences > UINT64_MAX / (occurrences - 1)) {
                    return -1;
                }

                contribution = occurrences * (occurrences - 1) / 2;

                if (total > UINT64_MAX - contribution) {
                    return -1;
                }

                total += contribution;
            }
        } else if (tuples[i].first < tuples[i].second) {
            Tuple reverse = {tuples[i].second, tuples[i].first};
            /* Possible weaknesses found:
             *  Variable 'match' can be declared as pointer to const [constVariablePointer]
             */
            Tuple *match = bsearch(&reverse, tuples, count, sizeof(*tuples),
                                   compare_tuples);

            if (match != NULL) {
                size_t index = (size_t)(match - tuples);
                size_t start = index;
                size_t end = index + 1;
                uint64_t reverse_occurrences;
                uint64_t contribution;

                while (start > 0 &&
                       tuples[start - 1].first == reverse.first &&
                       tuples[start - 1].second == reverse.second) {
                    --start;
                }

                while (end < count &&
                       tuples[end].first == reverse.first &&
                       tuples[end].second == reverse.second) {
                    ++end;
                }

                reverse_occurrences = (uint64_t)(end - start);

                if (occurrences > UINT64_MAX / reverse_occurrences) {
                    return -1;
                }

                contribution = occurrences * reverse_occurrences;

                if (total > UINT64_MAX - contribution) {
                    return -1;
                }

                total += contribution;
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

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid tuple count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Tuple count is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > 0) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            /* Possible weaknesses found:
             *  call to undeclared library function 'strerror' with type 'char *(int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'strerror' [-Wimplicit-function-declaration]
             *  include the header <string.h> or explicitly provide a declaration for 'strerror'
             */
            fprintf(stderr, "Allocation failed: %s\n", strerror(errno));
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%" SCNd64 " %" SCNd64,
                  &tuples[i].first, &tuples[i].second) != 2) {
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