#include <stdio.h>

int find_count(int arr[], int n, int x) {
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 50;
    int count = find_count(arr, n, x);
    if (count != -1) {
        printf("Element count before the record is %d\n", count);
    } else {
        printf("Element not found in the array\n");
    }
    return 0;
}