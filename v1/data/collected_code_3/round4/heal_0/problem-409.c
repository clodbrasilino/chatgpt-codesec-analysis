#include <stdio.h>
#include <stdlib.h>

int minProduct(int arr[], int n) {
    if (n < 2) {
        return -1;
    }
    int min_val = arr[0];
    int second_min_val = arr[1];
    for (int i = 2; i < n; i++) {
        if (arr[i] < min_val) {
            second_min_val = min_val;
            min_val = arr[i];
        } else if (arr[i] < second_min_val) {
            second_min_val = arr[i];
        }
    }
    return min_val * second_min_val;
}

int main() {
    int arr[] = {1, 4, 3, 2, 5, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    int min_product = minProduct(arr, n);
    printf("Minimum product is %d\n", min_product);
    return 0;
}