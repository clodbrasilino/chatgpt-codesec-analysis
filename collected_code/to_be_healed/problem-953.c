#include <stdio.h>

int findMinSubsets(int arr[], int size) {
    int count = 1;
    
    if (size == 0) {
        return 0;
    }
    
    for (int i = 1; i < size; i++) {
        int j;
        for (j = 0; j < i; j++)
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[i] == arr[j])
                break;
            
        if (i == j)
            count++;
    }
    
    return count;
}

int main() {
    int arr[] = { 1, 2, 3, 2, 4, 1, 5, 6, 3, 2 };
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int minSubsets = findMinSubsets(arr, size);
    
    printf("Minimum number of subsets with distinct elements: %d\n", minSubsets);
    
    return 0;
}