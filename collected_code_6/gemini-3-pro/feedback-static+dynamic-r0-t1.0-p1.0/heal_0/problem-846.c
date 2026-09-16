#include <stdio.h>
#include <stdlib.h>

int compareFunction(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int findPlatform(int arr[], int dep[], int n) {
    if (n == 0) {
        return 0;
    }

    qsort(arr, n, sizeof(int), compareFunction);
    qsort(dep, n, sizeof(int), compareFunction);

    int plat_needed = 1;
    int result = 1;
    int i = 1;
    int j = 0;

    while (i < n && j < n) {
        if (arr[i] <= dep[j]) {
            plat_needed++;
            i++;
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
        return 1;
    }

    int result = findPlatform(arr, dep, n);
    printf("Minimum number of Platforms required = %d\n", result);

    return 0;
}