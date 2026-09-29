#include <stdio.h>

int findFixedPoint(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == i) {
            return i;
        }
    }
    return -1;
}

int main() {
    const int arr[] = {-10, -5, 0, 3, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findFixedPoint(arr, n);
    if (result != -1) {
        printf("Fixed point is: %d\n", result);
    } else {
        printf("No fixed point found.\n");
    }
    return 0;
}