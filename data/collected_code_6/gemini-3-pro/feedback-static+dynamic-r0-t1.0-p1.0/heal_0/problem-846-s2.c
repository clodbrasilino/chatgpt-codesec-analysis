#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int findMinPlatforms(int arr[], int dep[], int n) {
    if (arr == NULL || dep == NULL || n <= 0) {
        return -1;
    }

    qsort(arr, n, sizeof(int), compare);
    qsort(dep, n, sizeof(int), compare);

    int platforms_needed = 1;
    int result = 1;
    int i = 1;
    int j = 0;

    while (i < n && j < n) {
        if (arr[i] <= dep[j]) {
            platforms_needed++;
            i++;
        } else {
            platforms_needed--;
            j++;
        }

        if (platforms_needed > result) {
            result = platforms_needed;
        }
    }

    return result;
}

int main() {
    int arr[] = {900, 940, 950, 1100, 1500, 1800};
    int dep[] = {910, 1200, 1120, 1130, 1900, 2000};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (n != sizeof(dep) / sizeof(dep[0])) {
        return EXIT_FAILURE;
    }

    int result = findMinPlatforms(arr, dep, n);
    
    if (result != -1) {
        printf("Minimum number of platforms required: %d\n", result);
    } else {
        printf("Invalid input or error occurred.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}