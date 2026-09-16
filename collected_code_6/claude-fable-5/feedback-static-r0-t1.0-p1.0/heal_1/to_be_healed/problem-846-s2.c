#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

static int find_min_platforms(const int *arrivals, const int *departures, size_t n, int *result)
{
    int *arr;
    int *dep;
    size_t i = 0;
    size_t j = 0;
    int platforms = 0;
    int max_platforms = 0;

    if (arrivals == NULL || departures == NULL || result == NULL || n == 0) {
        return -1;
    }

    arr = malloc(n * sizeof(*arr));
    if (arr == NULL) {
        return -1;
    }

    dep = malloc(n * sizeof(*dep));
    if (dep == NULL) {
        free(arr);
        return -1;
    }

    for (i = 0; i < n; i++) {
        arr[i] = arrivals[i];
        dep[i] = departures[i];
    }

    qsort(arr, n, sizeof(*arr), compare_ints);
    qsort(dep, n, sizeof(*dep), compare_ints);

    i = 0;
    j = 0;
    while (i < n && j < n) {
        if (arr[i] <= dep[j]) {
            platforms++;
            if (platforms > max_platforms) {
                max_platforms = platforms;
            }
            i++;
        } else {
            platforms--;
            j++;
        }
    }

    free(arr);
    free(dep);

    *result = max_platforms;
    return 0;
}

int main(void)
{
    int arrivals[] = { 900, 940, 950, 1100, 1500, 1800 };
    /* Possible weaknesses found:
     *  Variable 'departures' can be declared as const array [constVariable]
     */
    int departures[] = { 910, 1200, 1120, 1130, 1900, 2000 };
    size_t n = sizeof(arrivals) / sizeof(arrivals[0]);
    int min_platforms = 0;

    if (find_min_platforms(arrivals, departures, n, &min_platforms) != 0) {
        fprintf(stderr, "Error: failed to compute minimum platforms\n");
        return EXIT_FAILURE;
    }

    if (printf("Minimum number of platforms required: %d\n", min_platforms) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}