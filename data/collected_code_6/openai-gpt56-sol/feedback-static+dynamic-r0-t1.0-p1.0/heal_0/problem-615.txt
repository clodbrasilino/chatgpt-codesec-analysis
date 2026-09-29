#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const double *values;
    size_t length;
} Tuple;

static int average_of_tuples(const Tuple *tuples, size_t tuple_count, double *average)
{
    long double sum = 0.0L;
    size_t count = 0U;

    if (tuples == NULL || average == NULL) {
        return 0;
    }

    for (size_t i = 0U; i < tuple_count; ++i) {
        if (tuples[i].length > 0U && tuples[i].values == NULL) {
            return 0;
        }

        if (SIZE_MAX - count < tuples[i].length) {
            return 0;
        }

        for (size_t j = 0U; j < tuples[i].length; ++j) {
            sum += (long double)tuples[i].values[j];
        }

        count += tuples[i].length;
    }

    if (count == 0U) {
        return 0;
    }

    *average = (double)(sum / (long double)count);
    return 1;
}

int main(void)
{
    const double first[] = {1.0, 2.0, 3.0};
    const double second[] = {4.0, 5.0};
    const double third[] = {6.0, 7.0, 8.0, 9.0};
    const Tuple tuples[] = {
        {first, sizeof first / sizeof first[0]},
        {second, sizeof second / sizeof second[0]},
        {third, sizeof third / sizeof third[0]}
    };
    double average = 0.0;

    if (!average_of_tuples(
            tuples,
            sizeof tuples / sizeof tuples[0],
            &average)) {
        fputs("Unable to calculate the average.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Average: %.6f\n", average) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}