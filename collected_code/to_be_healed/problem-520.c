#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int lcm(int arr[], int n) {
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int result = arr[0];
    for (int i = 1; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        result = (result * arr[i]) / gcd(result, arr[i]);
    }
    return result;
}

int main() {
    int arr[] = {2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("LCM of array elements: %d\n", lcm(arr, n));
    return 0;
}