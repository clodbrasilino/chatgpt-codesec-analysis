#include <stdio.h>
#include <stdlib.h>

int findMissingNumber(int arr[], int n) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] != mid + arr[0]) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left + arr[0];
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter the elements of the array in sorted order: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int missingNumber = findMissingNumber(arr, n);
    printf("The missing number is: %d\n", missingNumber);

    free(arr);
    return EXIT_SUCCESS;
}