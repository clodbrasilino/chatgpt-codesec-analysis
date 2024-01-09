#include <stdio.h>

int minSwaps(int arr[], int n) {
    int cnt = 0;
    int zeroCount = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] == 0)
            zeroCount++;
    }

    for (int i = 0; i < zeroCount; i++) {
        if (arr[i] == 1)
            cnt++;
    }

    return cnt;
}

int main() {
    int arr[] = {0, 1, 0, 1, 1, 0};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = minSwaps(arr, n);

    printf("Minimum adjacent swaps required to sort the binary array is: %d\n", result);

    return 0;
}