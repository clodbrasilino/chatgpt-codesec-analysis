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
    int arr[] = {-10, -5, 0, 3, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int fixedPoint = findFixedPoint(arr, n);
    
    if (fixedPoint != -1) {
        printf("Fixed point is %d\n", fixedPoint);
    } else {
        printf("No fixed point found\n");
    }
    
    return 0;
}