#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

int findMinimumPlatforms(int arrival[], int departure[], size_t n) {
    if (n == 0 || arrival == NULL || departure == NULL) {
        return 0;
    }
    
    qsort(arrival, n, sizeof(int), compare);
    qsort(departure, n, sizeof(int), compare);
    
    int platforms_needed = 1;
    int max_platforms = 1;
    size_t i = 1;
    size_t j = 0;
    
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

int main(void) {
    int arrival[] = {900, 940, 950, 1100, 1500, 1800};
    int departure[] = {910, 1200, 1120, 1130, 1900, 2000};
    size_t arrival_count = sizeof(arrival) / sizeof(arrival[0]);
    size_t departure_count = sizeof(departure) / sizeof(departure[0]);
    
    if (arrival_count != departure_count) {
        fprintf(stderr, "Error: Array size mismatch\n");
        return EXIT_FAILURE;
    }
    
    int result = findMinimumPlatforms(arrival, departure, arrival_count);
    printf("Minimum platforms required: %d\n", result);
    
    return EXIT_SUCCESS;
}