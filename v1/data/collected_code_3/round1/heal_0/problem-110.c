#include <stdio.h>
#include <stdlib.h>

void findMissingRanges(int arr[], int n, int start, int end) {
    int i, j;
    for (i = start; i <= end; i++) {
        for (j = 0; j < n; j++) {
            if (arr[j] == i) {
                break;
            }
        }
        if (j == n) {
            printf("%d ", i);
        }
    }
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    int start = 1, end = 15;
    findMissingRanges(arr, n, start, end);
    return 0;
}