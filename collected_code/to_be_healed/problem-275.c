#include <stdio.h>

int lastRemovedElementPosition(int arr[], int n) {
    int i, lastRemovedPos;
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[n-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int removedElement = arr[n - 1];

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] == removedElement) {
            lastRemovedPos = i;
        }
    }

    /* Possible weaknesses found:
     *  use of uninitialized value 'lastRemovedPos' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    return lastRemovedPos;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int lastRemovedPos = lastRemovedElementPosition(arr, n);
    printf("Last removed element position: %d\n", lastRemovedPos);

    return 0;
}