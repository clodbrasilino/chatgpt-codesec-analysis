#include <stdio.h>
#include <stdbool.h>

bool isMinHeap(int arr[], int n) {
    for (int i = 0; i <= (n - 2) / 2; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[2*i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] > arr[2 * i + 1])
            return false;
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[2*i+2]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (2 * i + 2 < n && arr[i] > arr[2 * i + 2])
            return false;
    }
    return true;
}

int main() {
    int arr[] = {2, 3, 4, 5, 10, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (isMinHeap(arr, n))
        printf("Given array represents a min heap");
    else
        printf("Given array does not represent a min heap");

    return 0;
}