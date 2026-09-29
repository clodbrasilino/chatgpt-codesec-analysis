#include <stdio.h>
#include <stdbool.h>

bool checkPattern(int arr[], int n, int pattern[], int m) {
    int i = 0;
    int j = 0;

    while (i < n && j < m) {
        if (arr[i] == pattern[j]) {
            j++;
        }
        i++;
    }

    return j == m;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    int pattern[] = {1, 2, 3};

    int n = sizeof(arr) / sizeof(arr[0]);
    int m = sizeof(pattern) / sizeof(pattern[0]);

    if (checkPattern(arr, n, pattern, m)) {
        printf("Pattern found\n");
    } else {
        printf("Pattern not found\n");
    }

    return 0;
}