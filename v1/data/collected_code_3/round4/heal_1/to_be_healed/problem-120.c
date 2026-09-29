#include <stdio.h>

int maxProduct(int arr[], int n) {
    int max_val = arr[0];
    int min_val = arr[0];
    int maxProduct = arr[0];
    int end_min, end_max;

    for (int i = 1; i < n; i++) {
        end_max = max_val * arr[i];
        end_min = min_val * arr[i];

        /* Possible weaknesses found:
         *  implicit declaration of function 'max' [-Wimplicit-function-declaration]
         */
        max_val = max(arr[i], max(end_max, end_min));
        /* Possible weaknesses found:
         *  implicit declaration of function 'min' [-Wimplicit-function-declaration]
         */
        min_val = min(arr[i], min(end_max, end_min));

        maxProduct = max(maxProduct, max_val);
    }

    return maxProduct;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int arr[] = {1, -2, -3, 0, 7, -8, -2};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Maximum Product is %d", maxProduct(arr, n));
    return 0;
}