#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

int findMinimumPlatforms(const int arrival[], const int departure[], size_t n) {
    if (n == 0 || arrival == NULL || departure == NULL) {
        return 0;
    }
    
    int *sorted_arrival = malloc(n * sizeof(int));
    int *sorted_departure = malloc(n * sizeof(int));
    
    if (sorted_arrival == NULL || sorted_departure == NULL) {
        free(sorted_arrival);
        free(sorted_departure);
        return -1;
    }
    
    for (size_t k = 0; k < n; k++) {
        sorted_arrival[k] = arrival[k];
        sorted_departure[k] = departure[k];
    }
    
    qsort(sorted_arrival, n, sizeof(int), compare);
    qsort(sorted_departure, n, sizeof(int), compare);
    
    int platforms_needed = 1;
    int max_platforms = 1;
    size_t i = 1;
    size_t j = 0;
    
    while (i < n && j < n) {
        if (sorted_arrival[i] <= sorted_departure[j]) {
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
    
    free(sorted_arrival);
    free(sorted_departure);
    
    return max_platforms;
}

int main(void) {
    int arrival[] = {900, 940, 950, 1100, 1500, 1800};
    int departure[] = {910, 1200, 1120, 1130, 1900, 2000};
    size_t count = sizeof(arrival) / sizeof(arrival[0]);
    
    int result = findMinimumPlatforms(arrival, departure, count);
    printf("Minimum platforms required: %d\n", result);
    
    return EXIT_SUCCESS;
}