#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int find_min_removals(int arr[], int n, int k) {
    if (n <= 1) {
        return 0;
    }
    qsort(arr, n, sizeof(int), compare);
    int min_removals = n - 1;
    int left = 0;
    for (int right = 0; right < n; right++) {
        while (arr[right] - arr[left] > k) {
            left++;
        }
        int current_removals = n - (right - left + 1);
        if (current_removals < min_removals) {
            min_removals = current_removals;
        }
    }
    return min_removals;
}

int main() {
    int arr1[] = {1, 3, 4, 9, 10, 11, 12, 17, 20};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int k1 = 4;
    printf("%d\n", find_min_removals(arr1, n1, k1));

    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 2;
    printf("%d\n", find_min_removals(arr2, n2, k2));

    return 0;
}