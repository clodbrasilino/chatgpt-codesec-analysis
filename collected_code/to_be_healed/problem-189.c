#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'abs'
  */

int findMissingPositive(int arr[], int n) {
    int i;

    // Check if 1 is missing
    int contains1 = 0;
    for (i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] == 1) {
            contains1 = 1;
            break;
        }
    }

    if (contains1 == 0) {
        return 1;
    }

    // Mark elements that are out of range with 1
    for (i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] <= 0 || arr[i] > n) {
            arr[i] = 1;
        }
    }

    // Use array indexes to mark visited elements
    for (i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
         */
        int index = abs(arr[i]) - 1;
        if (index < n) {
            arr[index] = -abs(arr[index]);
        }
    }

    // Find first positive number
    for (i = 0; i < n; i++) {
        if (arr[i] > 0) {
            return i + 1;
        }
    }

    // All positive numbers found
    return n + 1;
}

int main() {
    int arr[] = {3, 4, -1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int missing = findMissingPositive(arr, n);
    printf("The first missing positive number is %d\n", missing);
    return 0;
}