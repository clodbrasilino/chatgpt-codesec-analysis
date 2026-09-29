#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y)
    {
        return -1;
    }
    if (x > y)
    {
        return 1;
    }
    return 0;
}

int find_minimum_platforms(const int *arrivals, const int *departures, size_t n, int *result)
{
    int *arr_sorted = NULL;
    int *dep_sorted = NULL;
    size_t i = 0;
    size_t j = 0;
    size_t buffer_size = 0;
    int platforms_needed = 0;
    int max_platforms = 0;

    if (arrivals == NULL || departures == NULL || result == NULL || n == 0)
    {
        return -1;
    }

    if (n > SIZE_MAX / sizeof(int))
    {
        return -1;
    }

    buffer_size = n * sizeof(int);

    arr_sorted = malloc(buffer_size);
    if (arr_sorted == NULL)
    {
        return -1;
    }

    dep_sorted = malloc(buffer_size);
    if (dep_sorted == NULL)
    {
        free(arr_sorted);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(arr_sorted, arrivals, buffer_size);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dep_sorted, departures, buffer_size);

    qsort(arr_sorted, n, sizeof(int), compare_ints);
    qsort(dep_sorted, n, sizeof(int), compare_ints);

    while (i < n && j < n)
    {
        if (arr_sorted[i] <= dep_sorted[j])
        {
            platforms_needed++;
            if (platforms_needed > max_platforms)
            {
                max_platforms = platforms_needed;
            }
            i++;
        }
        else
        {
            platforms_needed--;
            j++;
        }
    }

    free(arr_sorted);
    free(dep_sorted);

    *result = max_platforms;
    return 0;
}

int main(void)
{
    const int arrivals[] = {900, 940, 950, 1100, 1500, 1800};
    const int departures[] = {910, 1200, 1120, 1130, 1900, 2000};
    size_t n = sizeof(arrivals) / sizeof(arrivals[0]);
    int min_platforms = 0;

    if (find_minimum_platforms(arrivals, departures, n, &min_platforms) != 0)
    {
        fprintf(stderr, "Error: failed to compute minimum platforms\n");
        return EXIT_FAILURE;
    }

    if (printf("Minimum number of platforms required: %d\n", min_platforms) < 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}