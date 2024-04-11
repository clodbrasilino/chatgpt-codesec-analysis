#include <stdio.h>

int find_frequency(int arr[], int n, int x) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            count++;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 2, 2, 3, 1, 1, 2, 5, 6, 7, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 2;
    printf("Frequency of %d is %d", x, find_frequency(arr, n, x));
    return 0;
}