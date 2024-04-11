#include <stdio.h>

int find_count(int arr[], int n, int x) {
    int i, count = 0;
    for (i = 0; i < n; i++) {
        if (arr[i] == x) {
            break;
        }
        count++;
    }
    return count;
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 50;
    printf("Count of elements before %d is %d\n", x, find_count(arr, n, x));
    return 0;
}