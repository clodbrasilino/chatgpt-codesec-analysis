#include <stdio.h>

int hasDecreasingTrend(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] <= arr[i+1]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int arr[] = {5, 4, 3, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);

    if (hasDecreasingTrend(arr, size)) {
        printf("The sequence has a decreasing trend.\n");
    } else {
        printf("The sequence does not have a decreasing trend.\n");
    }

    return 0;
}