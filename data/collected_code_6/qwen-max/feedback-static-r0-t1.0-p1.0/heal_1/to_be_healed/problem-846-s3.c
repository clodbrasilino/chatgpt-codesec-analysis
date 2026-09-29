#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int findPlatform(int arr[], int dep[], int n) {
    qsort(arr, n, sizeof(int), compare);
    qsort(dep, n, sizeof(int), compare);

    int platform_needed = 1, result = 1;
    int i = 1, j = 0;

    while (i < n && j < n) {
        /* Possible weaknesses found:
         *  Assuming condition 'arr[i]<=dep[j]' is false
         */
        if (arr[i] <= dep[j]) {
            platform_needed++;
            i++;
        /* Possible weaknesses found:
         *  Condition 'arr[i]>dep[j]' is always true [knownConditionTrueFalse]
         *  Condition 'arr[i]>dep[j]' is always true
         */
        } else if (arr[i] > dep[j]) {
            platform_needed--;
            j++;
        }
        if (platform_needed > result)
            result = platform_needed;
    }

    return result;
}

int main() {
    int arr[] = {900, 940, 950, 1100, 1500, 1800};
    int dep[] = {910, 1200, 1120, 1130, 1900, 2000};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Minimum number of platforms required = %d\n", findPlatform(arr, dep, n));

    return 0;
}