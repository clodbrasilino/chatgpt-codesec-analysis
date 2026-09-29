#include <stdio.h>
#include <stdlib.h>

int find_min_platforms(int arr[], int dep[], int n) {
    int i = 1, j = 0;
    int platforms = 1, result = 1;

    while (i < n && j < n) {
        if (arr[i] <= dep[j]) {
            platforms++;
            if (platforms > result) {
                result = platforms;
            }
            i++;
        } else {
            platforms--;
            j++;
        }
    }
    return result;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int arr[] = {900, 940, 950, 1100, 1500, 1800};
    int dep[] = {910, 1200, 1120, 1130, 1900, 2000};
    int n = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, n, sizeof(int), compare);
    qsort(dep, n, sizeof(int), compare);

    int min_platforms = find_min_platforms(arr, dep, n);
    printf("%d\n", min_platforms);

    return 0;
}