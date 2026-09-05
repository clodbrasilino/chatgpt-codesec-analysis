#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int findTriplet(int arr[], int n, int sum) {
    if (arr == NULL || n < 3) {
        return 0;
    }

    qsort(arr, n, sizeof(int), compare);

    for (int i = 0; i < n - 2; i++) {
        int left = i + 1;
        int right = n - 1;

        while (left < right) {
            int currentSum = arr[i] + arr[left] + arr[right];

            if (currentSum == sum) {
                printf("Triplet found: %d, %d, %d\n", arr[i], arr[left], arr[right]);
                return 1;
            } else if (currentSum < sum) {
                left++;
            } else {
                right--;
            }
        }
    }

    return 0;
}

int main(void) {
    int arr[] = {12, 3, 4, 1, 6, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 24;

    if (!findTriplet(arr, n, sum)) {
        printf("No triplet found with sum %d\n", sum);
    }

    return 0;
}