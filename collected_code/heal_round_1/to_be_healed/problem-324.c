#include <stdio.h>

int sumAlternateChains(int a[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i = i + 4) {
        /* Possible weaknesses found:
         *  Cannot determine that 'a[i+2]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'a[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        sum += a[i] + a[i + 2];
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = sumAlternateChains(arr, size);
    printf("Sum of alternate chains: %d\n", result);
    return 0;
}