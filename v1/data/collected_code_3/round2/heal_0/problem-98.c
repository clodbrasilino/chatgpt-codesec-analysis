#include <stdio.h>

double averageProduct(int arr[], int n) {
    int i;
    double product = 1;
    for (i = 0; i < n; i++) {
        product *= arr[i];
    }
    return product / n;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Average product is %f", averageProduct(arr, n));
    return 0;
}