#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int findGcd(int arr[], int n) {
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int result = arr[0];
    for (int i = 1; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        result = gcd(arr[i], result);
        if (result == 1) {
            return 1;
        }
    }
    return result;
}

int main() {
    int arr[] = {32, 18, 24};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findGcd(arr, n);
    printf("GCD is %d\n", result);
    return 0;
}