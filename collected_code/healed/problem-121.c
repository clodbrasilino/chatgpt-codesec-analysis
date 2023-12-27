#include <stdio.h>

void findTriplet(int *arr, const int n, const int targetSum) {
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                if (arr[i] + arr[j] + arr[k] == targetSum) {
                    printf("%d, %d, %d\n", arr[i], arr[j], arr[k]);
                }
            }
        }
    }
}

int main() {
    int n, targetSum;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements of the array: ");

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the target sum: ");
    scanf("%d", &targetSum);

    printf("Triplets with sum %d are:\n", targetSum);
    findTriplet(arr, n, targetSum);

    return 0;
}