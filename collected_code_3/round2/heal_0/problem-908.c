#include <stdio.h>

int fixedPoint(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == i)
            return i;
    }
    return -1;
}

int main() {
    int arr[] = {0, 2, 5, 8, 17};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Fixed Point is %d", fixedPoint(arr, n));
    return 0;
}