#include <stddef.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

typedef struct {
    const double *values;
    size_t length;
} Tuple;

int tuple_average(const Tuple *tuples, size_t tuple_count, double *average)
{
    double sum = 0.0;
    size_t count = 0;

    if (tuples == NULL || average == NULL) {
        return -1;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        if (tuples[i].length > 0 && tuples[i].values == NULL) {
            return -1;
        }

        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'SIZE_MAX'
         *  'SIZE_MAX' undeclared (first use in this function)
         */
        if (tuples[i].length > SIZE_MAX - count) {
            return -1;
        }

        for (size_t j = 0; j < tuples[i].length; ++j) {
            sum += tuples[i].values[j];
        }

        count += tuples[i].length;
    }

    if (count == 0) {
        return -1;
    }

    *average = sum / (double)count;
    return 0;
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

    if (tuple_average(tuples, sizeof tuples / sizeof tuples[0], &average) != 0) {
        fputs("Unable to calculate the average.\n", stderr);
        return 1;
    }

    if (printf("Average: %.2f\n", average) < 0) {
        return 1;
    }

    return 0;
}