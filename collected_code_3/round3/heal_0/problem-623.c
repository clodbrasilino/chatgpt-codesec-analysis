#include <stdio.h>
#include <math.h>

void nthPower(int arr[], int n, int size) {
    for(int i = 0; i < size; i++) {
        arr[i] = pow(arr[i], n);
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr)/sizeof(arr[0]);
    int n = 2;

    nthPower(arr, n, size);

    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}