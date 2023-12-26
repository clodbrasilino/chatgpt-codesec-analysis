#include <stdio.h>

int countInversions(int arr[], int n) {
    int invCount = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[i] > arr[j]) {
                invCount++;
            }
        }
    }
    return invCount;
}

int main() {
    int arr[] = {1, 3, 5, 2, 4, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int numInversions = countInversions(arr, n);
    printf("Number of inversions: %d\n", numInversions);
    
    return 0;
}