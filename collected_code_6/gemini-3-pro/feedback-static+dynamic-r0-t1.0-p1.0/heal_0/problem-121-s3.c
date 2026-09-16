#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

bool findTriplet(int arr[], int n, int target) {
    if (n < 3) {
        return false;
    }

    qsort(arr, n, sizeof(int), compare);

    for (int i = 0; i < n - 2; i++) {
        int left = i + 1;
        int right = n - 1;

        while (left < right) {
            int sum = arr[i] + arr[left] + arr[right];

            if (sum == target) {
                printf("Triplet is %d, %d, %d\n", arr[i], arr[left], arr[right]);
                return true;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }

    return false;
}

int main(void) {
    int arr[] = {1, 4, 45, 6, 10, 8};
    int target = 22;
    int n = sizeof(arr) / sizeof(arr[0]);

    if (!findTriplet(arr, n, target)) {
        printf("Triplet not found.\n");
    }

    return 0;
}