#include <stdio.h>
#include <stdbool.h>

bool has_majority(int *arr, int n) {
    if (n == 0) return false;
    int candidate = arr[0];
    int count = 1;
    for (int i = 1; i < n; ++i) {
        if (arr[i] == candidate) {
            count++;
            if (count > n / 2) return true;
        } else if (arr[i] != candidate) {
            candidate = arr[i];
            count = 1;
        }
    }
    return false;
}

int main() {
    int arr[] = {1, 1, 2, 3, 3, 3, 3, 4, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    if (has_majority(arr, n)) {
        printf("Array has a majority element.\n");
    } else {
        printf("Array does not have a majority element.\n");
    }
    return 0;
}