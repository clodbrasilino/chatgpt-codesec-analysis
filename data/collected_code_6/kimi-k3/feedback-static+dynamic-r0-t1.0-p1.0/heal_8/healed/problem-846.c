#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int compare(const void *a, const void *b)
{
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int findMinPlatforms(int arrival[], int departure[], int n)
{
    if (arrival == NULL || departure == NULL || n <= 0) {
        return 0;
    }

    qsort(arrival, (size_t)n, sizeof(int), compare);
    qsort(departure, (size_t)n, sizeof(int), compare);

    int platforms_needed = 1;
    int max_platforms = 1;
    int i = 1;
    int j = 0;

    while (i < n && j < n) {
        if (arrival[i] <= departure[j]) {
            platforms_needed++;
            i++;
        } else {
            platforms_needed--;
            j++;
        }

        if (platforms_needed > max_platforms) {
            max_platforms = platforms_needed;
        }
    }

    return max_platforms;
}

int main(void)
{
    int arrival[] = {900, 940, 950, 1100, 1500, 1800};
    int departure[] = {910, 1200, 1120, 1130, 1900, 2000};

    size_t arrival_size = sizeof(arrival) / sizeof(arrival[0]);
    size_t departure_size = sizeof(departure) / sizeof(departure[0]);

    if (arrival_size > (size_t)INT_MAX || departure_size > (size_t)INT_MAX) {
        fprintf(stderr, "Error: Array size too large\n");
        return EXIT_FAILURE;
    }

    int n = (int)arrival_size;

    int result = findMinPlatforms(arrival, departure, n);
    printf("Minimum platforms required: %d\n", result);

    return EXIT_SUCCESS;
}