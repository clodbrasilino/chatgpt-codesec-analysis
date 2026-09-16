#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int findTripletWithSum(int arr[], int n, int sum) {
    qsort(arr, n, sizeof(int), compare);
    for (int i = 0; i < n - 2; i++) {
        int left = i + 1;
        int right = n - 1;
        while (left < right) {
            int current_sum = arr[i] + arr[left] + arr[right];
            if (current_sum == sum) {
                printf("Triplet found: %d, %d, %d\n", arr[i], arr[left], arr[right]);
                return 1;
            } else if (current_sum < sum) {
                left++;
            } else {
                right--;
            }
        }
    }
    return 0;
}

int main() {
    int arr[] = {12, 3, 4, 1, 6, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 24;

    if (findTripletWithSum(arr, n, sum) == 0) {
        printf("No triplet found with the given sum.\n");
    }

    return 0;
}