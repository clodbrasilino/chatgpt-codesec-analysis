#include <stdio.h>
#include <stdlib.h>

int maxProduct(int* arr, int n) {
    if (n == 0)
        return 0;

    int maxVal = arr[0];
    int minVal = arr[0];
    int maxProduct = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] < 0) {
            int tmp = maxVal;
            maxVal = minVal;
            minVal = tmp;
        }

        /* Possible weaknesses found:
         *  implicit declaration of function 'max' [-Wimplicit-function-declaration]
         */
        maxVal = max(maxVal * arr[i], arr[i]);
        /* Possible weaknesses found:
         *  implicit declaration of function 'min' [-Wimplicit-function-declaration]
         */
        minVal = min(minVal * arr[i], arr[i]);

        maxProduct = max(maxProduct, maxVal);
    }

    return maxProduct;
}

int max(int x, int y) {
    return x > y ? x : y;
}

int min(int x, int y) {
    return x < y ? x : y;
}

int main() {
    int arr[] = {1, -2, -3, 0, 7, -8, -2};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Maximum Subarray product is %d\n", maxProduct(arr, n));
    return 0;
}