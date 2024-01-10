#include <stdio.h>

int findElement(int arr[], int n, int k) {
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[i] == arr[j])
                count++;
        }
        if (count == k)
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            return arr[i];
    }
    return -1;
}

int main() {
    int arr[] = {1, 2, 2, 3, 4, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    int result = findElement(arr, n, k);
    
    if (result == -1)
        printf("No element occurring %d times\n", k);
    else
        printf("First element occurring %d times: %d\n", k, result);
        
    return 0;
}