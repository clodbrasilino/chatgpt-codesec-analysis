#include <stdio.h>

int findFixedPoint(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == i) {
            return i;
        }
    }
    return -1;
}

int main() {
    int arr[] = { -10, -1, 0, 3, 10, 11, 30, 50, 100 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findFixedPoint(arr, n);

    if (result == -1) {
        printf("No Fixed Point\n");
    } else {
        printf("Fixed Point is %d\n", result);
    }
    return 0;
}