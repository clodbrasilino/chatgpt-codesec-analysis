#include <stdio.h>

void modifyRunLengthEncoding(int arr[], int n) {
    int i = 0, j = 0;
    while (i < n) {
        int count = 1;
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        while (i < n - 1 && arr[i] == arr[i + 1]) {
            count++;
            i++;
        }
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        printf("%d %d ", count, arr[i]);
        i++;
    }
}

int main() {
    int arr[] = {1, 1, 2, 3, 3, 3, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    modifyRunLengthEncoding(arr, n);
    return 0;
}