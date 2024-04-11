#include <stdio.h>
#include <stdbool.h>

bool isRepeated(int arr[], int i, int num) {
    for (int j = 0; j < i; j++) {
        if (arr[j] == num) {
            return true;
        }
    }
    return false;
}

int productOfNonRepeated(int arr[], int n) {
    int product = 1;
    for (int i = 0; i < n; i++) {
        if (!isRepeated(arr, i, arr[i])) {
            product *= arr[i];
        }
    }
    return product;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Product of non-repeated elements: %d\n", productOfNonRepeated(arr, n));
    return 0;
}