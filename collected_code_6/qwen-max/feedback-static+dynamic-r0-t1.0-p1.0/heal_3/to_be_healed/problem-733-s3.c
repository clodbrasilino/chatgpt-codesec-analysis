#include <stdio.h>

int findFirstOccurrence(const int arr[], int n, int key) {
    int low = 0, high = n - 1, result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) {
            result = mid;
            high = mid - 1;
        } else if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

int main() {
    const int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    /* Possible weaknesses found:
     *  Variable 'test_cases' can be declared as const array [constVariable]
     */
    int test_cases[] = {1, 2, 3, 4, 5, 6, 7, 0, 8};
    for (int i = 0; i < 9; i++) {
        int key = test_cases[i];
        int index = findFirstOccurrence(arr, n, key);
        if (index != -1) {
            printf("Element %d found at index: %d\n", key, index);
        } else {
            printf("Element %d not found\n", key);
        }
    }
    return 0;
}