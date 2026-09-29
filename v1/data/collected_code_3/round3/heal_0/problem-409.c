#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int minProduct(int arr[], int n) {
    qsort(arr, n, sizeof(int), compare);
    int product = 1;
    for (int i = 0; i < n; i += 2) {
        product *= arr[i] * arr[i + 1];
    }
    return product;
}

int main() {
    int arr[] = {1, 3, 2, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Minimum product is %d", minProduct(arr, n));
    return 0;
}