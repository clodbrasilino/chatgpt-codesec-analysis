#include <stdio.h>
#include <stdbool.h>

bool has_majority(const int *arr, int n) {
    int candidate = arr[0];
    int count = 1;

    for (int i = 1; i < n; ++i) {
        if (arr[i] == candidate) {
            count++;
            if (count > n / 2) return true;
        } else {
            candidate = arr[i];
            count = 1;
        }
    }

    return false;
}

int main() {
    int arr[] = {1, 2, 3, 3, 3, 3, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (has_majority(arr, n)) {
        printf("Majority element exists\n");
    } else {
        printf("No majority element\n");
    }

    return 0;
}