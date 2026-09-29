#include <stdio.h>
#include <stdlib.h>

int compareAttributes(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int findPlatform(int arr[], int dep[], int n) {
    if (n == 0) {
        return 0;
    }

    qsort(arr, n, sizeof(int), compareAttributes);
    qsort(dep, n, sizeof(int), compareAttributes);

    int plat_needed = 1;
    int result = 1;
    int i = 1, j = 0;

    while (i < n && j < n) {
        /* Possible weaknesses found:
         *  Assuming condition 'arr[i]<=dep[j]' is false
         */
        if (arr[i] <= dep[j]) {
            plat_needed++;
            i++;
        /* Possible weaknesses found:
         *  Condition 'arr[i]>dep[j]' is always true
         *  Condition 'arr[i]>dep[j]' is always true [knownConditionTrueFalse]
         */
        } else if (arr[i] > dep[j]) {
            plat_needed--;
            j++;
        }

        if (plat_needed > result) {
            result = plat_needed;
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

    int platforms = findPlatform(arr, dep, n);
    printf("Minimum Number of Platforms Required = %d\n", platforms);

    return EXIT_SUCCESS;
}