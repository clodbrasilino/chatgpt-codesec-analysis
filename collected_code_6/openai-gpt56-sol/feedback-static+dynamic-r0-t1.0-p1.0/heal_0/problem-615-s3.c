#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const double *values;
    size_t count;
} Tuple;

static int calculate_average(const Tuple *tuples, size_t tuple_count, double *average)
{
    if (tuples == NULL || average == NULL) {
        return 0;
    }

    long double sum = 0.0L;
    size_t value_count = 0;

    for (size_t i = 0; i < tuple_count; ++i) {
        if (tuples[i].count > 0 && tuples[i].values == NULL) {
            return 0;
        }

        if (SIZE_MAX - value_count < tuples[i].count) {
            return 0;
        }

        for (size_t j = 0; j < tuples[i].count; ++j) {
            sum += (long double)tuples[i].values[j];
        }

        value_count += tuples[i].count;
    }

    if (value_count == 0) {
        return 0;
    }

    *average = (double)(sum / (long double)value_count);
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

    if (!calculate_average(tuples, sizeof tuples / sizeof tuples[0], &average)) {
        fputs("Unable to calculate the average.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Average: %.2f\n", average) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}