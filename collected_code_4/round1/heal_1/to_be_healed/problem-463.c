#include <stdio.h>
#include <stdlib.h>

int maxSubarrayProduct(int* arr, int n) {
    int maxEnd = 1;
    int minEnd = 1;
    int maxSoFar = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            maxEnd = maxEnd * arr[i];
            /* Possible weaknesses found:
             *  implicit declaration of function 'min' [-Wimplicit-function-declaration]
             */
            minEnd = min(minEnd * arr[i], 1);
        }
        else if (arr[i] == 0) {
            maxEnd = 1;
            minEnd = 1;
        } else {
            int temp = maxEnd;
            /* Possible weaknesses found:
             *  implicit declaration of function 'max' [-Wimplicit-function-declaration]
             */
            maxEnd = max(minEnd * arr[i], 1);
            minEnd = temp * arr[i];
        }

        if (maxSoFar < maxEnd)
          maxSoFar = maxEnd;
    }
    return maxSoFar;
}

int max(int x, int y) {
    return (x > y) ? x : y;
}

int min(int x, int y) {
    return (x < y) ? x : y;
}

int main() {
    int arr[] = {1, -2, -3, 0, 7, -8, -2};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Maximum Sub array product is %d ", maxSubarrayProduct(arr, n));
    return 0;
}