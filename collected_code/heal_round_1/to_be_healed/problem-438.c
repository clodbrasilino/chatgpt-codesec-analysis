#include<stdio.h>

int countBidirectionalTuples(int arr[], int n) {
    int count = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[j+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if(arr[i] == arr[j] && arr[j + 1] == arr[i + 1]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 2, 1, 2, 2, 3, 4, 4, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = countBidirectionalTuples(arr, n);
    printf("Count of bidirectional tuple pairs: %d\n", result);
    return 0;
}