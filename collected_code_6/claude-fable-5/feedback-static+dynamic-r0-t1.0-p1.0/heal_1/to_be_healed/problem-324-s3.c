#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int even_sum;
    int odd_sum;
} ChainSums;

int sum_alternate_chains(const Tuple *tuples, size_t count, ChainSums *result)
{
    size_t i;
    size_t index;
    /* Possible weaknesses found:
     *  The scope of the variable 'value' can be reduced. [variableScope]
     */
    int value;

    if (tuples == NULL || result == NULL) {
        return -1;
    }

    result->even_sum = 0;
    result->odd_sum = 0;
    index = 0;

    for (i = 0; i < count; i++) {
        value = tuples[i].first;
        if (index % 2U == 0U) {
            result->even_sum += value;
        } else {
            result->odd_sum += value;
        }
        index++;

        value = tuples[i].second;
        if (index % 2U == 0U) {
            result->even_sum += value;
        } else {
            result->odd_sum += value;
        }
        index++;
    }

    return 0;
}

int main(void)
{
    Tuple data[] = { {5, 6}, {3, 6}, {8, 9}, {4, 6} };
    size_t count = sizeof(data) / sizeof(data[0]);
    ChainSums sums;

    if (sum_alternate_chains(data, count, &sums) != 0) {
        fprintf(stderr, "Error computing alternate chain sums\n");
        return EXIT_FAILURE;
    }

    if (printf("Sum of alternate chain 1: %d\n", sums.even_sum) < 0) {
        return EXIT_FAILURE;
    }
    if (printf("Sum of alternate chain 2: %d\n", sums.odd_sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}