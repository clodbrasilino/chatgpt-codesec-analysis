#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int minimum_platforms(const int arrivals[], const int departures[],
                             size_t count, size_t *result)
{
    int *sorted_arrivals = NULL;
    int *sorted_departures = NULL;
    size_t arrival_index = 0U;
    size_t departure_index = 0U;
    size_t current_platforms = 0U;
    size_t maximum_platforms = 0U;

    if (result == NULL || (count > 0U &&
        (arrivals == NULL || departures == NULL))) {
        return -1;
    }

    *result = 0U;

    if (count == 0U) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*sorted_arrivals)) {
        return -1;
    }

    sorted_arrivals = malloc(count * sizeof(*sorted_arrivals));
    sorted_departures = malloc(count * sizeof(*sorted_departures));

    if (sorted_arrivals == NULL || sorted_departures == NULL) {
        free(sorted_arrivals);
        free(sorted_departures);
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (arrivals[i] < 0 || departures[i] < arrivals[i]) {
            free(sorted_arrivals);
            free(sorted_departures);
            return -1;
        }

        sorted_arrivals[i] = arrivals[i];
        sorted_departures[i] = departures[i];
    }

    qsort(sorted_arrivals, count, sizeof(*sorted_arrivals), compare_ints);
    qsort(sorted_departures, count, sizeof(*sorted_departures), compare_ints);

    while (arrival_index < count) {
        if (departure_index < count &&
            sorted_departures[departure_index] < sorted_arrivals[arrival_index]) {
            if (current_platforms == 0U) {
                free(sorted_arrivals);
                free(sorted_departures);
                return -1;
            }

            --current_platforms;
            ++departure_index;
        } else {
            ++current_platforms;

            if (current_platforms > maximum_platforms) {
                maximum_platforms = current_platforms;
            }

            ++arrival_index;
        }
    }

    free(sorted_arrivals);
    free(sorted_departures);

    *result = maximum_platforms;
    return 0;
}

int main(void)
{
    const int arrivals[] = {900, 940, 950, 1100, 1500, 1800};
    const int departures[] = {910, 1200, 1120, 1130, 1900, 2000};
    const size_t count = sizeof(arrivals) / sizeof(arrivals[0]);
    size_t platforms = 0U;

    if (count != sizeof(departures) / sizeof(departures[0])) {
        fputs("Input size mismatch\n", stderr);
        return EXIT_FAILURE;
    }

    if (minimum_platforms(arrivals, departures, count, &platforms) != 0) {
        fputs("Unable to calculate the minimum number of platforms\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", platforms) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}