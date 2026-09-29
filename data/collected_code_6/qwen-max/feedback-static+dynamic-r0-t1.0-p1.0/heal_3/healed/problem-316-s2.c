#include <stdio.h>

int findLastOccurrence(const int arr[], int n, int key) {
    int left = 0;
    int right = n - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key) {
            result = mid;
            left = mid + 1;
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

int main() {
    const int arr[] = {1, 2, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    const int test_cases[] = {2, 3, 4, 9, 6};
    for (int i = 0; i < 5; i++) {
        int key = test_cases[i];
        int index = findLastOccurrence(arr, n, key);

        if (index != -1) {
            printf("Index of the last occurrence of %d is: %d\n", key, index);
        } else {
            printf("%d not found in the array.\n", key);
        }
    }

    return 0;
}