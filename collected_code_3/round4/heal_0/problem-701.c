#include <stdio.h>

int equilibriumIndex(int arr[], int n) {
    int sum = 0;
    int leftSum = 0;
    int i;

    for (i = 0; i < n; ++i) {
        sum += arr[i];
    }

    for (i = 0; i < n; ++i) {
        sum -= arr[i];

        if (leftSum == sum) {
            return i;
        }

        leftSum += arr[i];
    }

    return -1;
}

int main() {
    int arr[] = {-7, 1, 5, 2, -4, 3, 0};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", equilibriumIndex(arr, arrSize));
    return 0;
}