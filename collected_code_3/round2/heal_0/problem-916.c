#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

bool findTriplet(int arr[], int n, int sum) {
    int l, r;
    qsort(arr, n, sizeof(int), compare);
    for (int i = 0; i < n - 2; i++) {
        l = i + 1;
        r = n - 1;
        while (l < r) {
            if (arr[i] + arr[l] + arr[r] == sum) {
                return true;
            } else if (arr[i] + arr[l] + arr[r] < sum) {
                l++;
            } else {
                r--;
            }
        }
    }
    return false;
}

int main() {
    int arr[] = {1, 4, 45, 6, 10, 8};
    int sum = 22;
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    if (findTriplet(arr, arr_size, sum)) {
        printf("Triplet found\n");
    } else {
        printf("No triplet found\n");
    }
    return 0;
}