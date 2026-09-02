#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int tripletSum(int arr[], int n, int target) {
    qsort(arr, n, sizeof(int), compare);

    for (int i = 0; i < n - 2; ++i) {
        int left = i + 1;
        int right = n - 1;

        while (left < right) {
            int sum = arr[i] + arr[left] + arr[right];

            if (sum == target) {
                printf("Triplet: %d, %d, %d\n", arr[i], arr[left], arr[right]);
                return 1;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }
    return 0;
}

int main() {
    int arr[] = {1, 4, 45, 6, 10, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 22;

    if (tripletSum(arr, n, target)) {
        printf("Triplet found with the given sum.\n");
    } else {
        printf("No triplet found with the given sum.\n");
    }

    return 0;
}