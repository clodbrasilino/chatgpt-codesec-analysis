#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int minimum_platforms(int arrivals[], int departures[], size_t count)
{
    if (arrivals == NULL || departures == NULL || count == 0U) {
        return 0;
    }

    qsort(arrivals, count, sizeof(*arrivals), compare_ints);
    qsort(departures, count, sizeof(*departures), compare_ints);

    size_t arrival_index = 0U;
    size_t departure_index = 0U;
    int platforms_in_use = 0;
    int minimum_required = 0;

    while (arrival_index < count) {
        if (departure_index == count ||
            arrivals[arrival_index] <= departures[departure_index]) {
            ++platforms_in_use;
            if (platforms_in_use > minimum_required) {
                minimum_required = platforms_in_use;
            }
            ++arrival_index;
        } else {
            if (platforms_in_use > 0) {
                --platforms_in_use;
            }
            ++departure_index;
        }
    }

    return minimum_required;
}

int main(void)
{
    int arrivals[] = {900, 940, 950, 1100, 1500, 1800};
    int departures[] = {910, 1200, 1120, 1130, 1900, 2000};
    const size_t count = sizeof(arrivals) / sizeof(arrivals[0]);

    if (count != sizeof(departures) / sizeof(departures[0])) {
        fputs("Mismatched schedule data\n", stderr);
        return EXIT_FAILURE;
    }

    const int result = minimum_platforms(arrivals, departures, count);

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}