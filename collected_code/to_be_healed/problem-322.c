#include <stdio.h>

void findMinIndex(int arr[], int n) {
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int min = arr[0];
    for (int i = 1; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] < min) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            min = arr[i];
        }
    }
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] == min) {
            printf("%d ", i);
        }
    }
}

int main() {
    int arr[] = {10, 3, 5, 2, 10, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Index positions of minimum values: ");
    findMinIndex(arr, n);
    return 0;
}