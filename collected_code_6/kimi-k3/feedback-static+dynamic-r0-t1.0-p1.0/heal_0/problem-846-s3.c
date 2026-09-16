#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int find_min_platforms(int arrival[], int departure[], int n) {
    if (n <= 0 || arrival == NULL || departure == NULL) {
        return 0;
    }

    qsort(arrival, n, sizeof(int), compare);
    qsort(departure, n, sizeof(int), compare);

    int platforms_needed = 1;
    int max_platforms = 1;
    int i = 1;
    int j = 0;

    while (i < n && j < n) {
        if (arrival[i] <= departure[j]) {
            platforms_needed++;
            i++;
            if (platforms_needed > max_platforms) {
                max_platforms = platforms_needed;
            }
        } else {
            platforms_needed--;
            j++;
        }
    }

    return max_platforms;
}

int main(void) {
    int arrival[] = {900, 940, 950, 1100, 1500, 1800};
    int departure[] = {910, 1200, 1120, 1130, 1900, 2000};
    int n = sizeof(arrival) / sizeof(arrival[0]);

    if (n == 0) {
        fprintf(stderr, "Error: Empty schedule\n");
        return EXIT_FAILURE;
    }

    int result = find_min_platforms(arrival, departure, n);
    printf("Minimum platforms required: %d\n", result);

    return EXIT_SUCCESS;
}