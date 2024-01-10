#include <stdio.h>

int minSwaps(int arr[], int n) {
    int cnt = 0;
    int zeroCount = 0;

    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] == 0)
            zeroCount++;
    }

    for (int i = 0; i < zeroCount; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
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