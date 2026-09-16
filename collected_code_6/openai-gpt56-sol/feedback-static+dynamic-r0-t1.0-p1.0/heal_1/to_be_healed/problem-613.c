#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'Tuple::id' is never used. [unusedStructMember]
     */
    int id;
    double value;
} Tuple;

bool find_max_value(const Tuple *tuples, size_t count, double *max_value)
{
    if (tuples == NULL || max_value == NULL || count == 0U) {
        return false;
    }

    double maximum = tuples[0].value;

    for (size_t i = 1U; i < count; ++i) {
        if (tuples[i].value > maximum) {
            maximum = tuples[i].value;
        }
    }

    *max_value = maximum;
    return true;
}

int main(void)
{
    const Tuple tuples[] = {
        {1, 12.5},
        {2, 47.8},
        {3, 23.1},
        {4, 91.4},
        {5, 38.6}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);
    double maximum = 0.0;

    if (!find_max_value(tuples, count, &maximum)) {
        fputs("Unable to find the maximum value.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Maximum value: %.2f\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}