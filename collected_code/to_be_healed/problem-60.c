#include <stdio.h>

int findMaxLength(int arr[], int n) {
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  Cannot determine that 'arr[1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int max = 1, curr = 1, diff = arr[1] - arr[0];
    for (int i = 1; i < n - 1; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i + 1] - arr[i] == diff) {
            curr++;
        } else {
            if (curr > max) {
                max = curr;
            }
            curr = 1;
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            diff = arr[i + 1] - arr[i];
        }
    }

    if (curr > max) {
        max = curr;
    }

    return max;
}

int main() {
    int arr[] = {3, 8, 4, 5, 6, 2, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    int maxLength = findMaxLength(arr, n);

    printf("Maximum length of subsequence with adjacent difference: %d\n", maxLength);

    return 0;
}