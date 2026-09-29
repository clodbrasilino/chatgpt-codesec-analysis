#include <stdio.h>
#include <stdbool.h>

bool checkSequence(int arr[], int n, int pattern[], int m) {
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (arr[i] == pattern[j]) {
            i++;
            j++;
        } else {
            i++;
        }
    }
    return (j == m);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int pattern[] = {1, 3, 5, 7, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int m = sizeof(pattern) / sizeof(pattern[0]);

    if (checkSequence(arr, n, pattern, m)) {
        printf("Pattern sequence found in the array.\n");
    } else {
        printf("Pattern sequence not found in the array.\n");
    }

    return 0;
}