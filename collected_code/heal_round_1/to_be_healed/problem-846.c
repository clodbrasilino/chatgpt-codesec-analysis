#include <stdio.h>

int findMinPlatforms(int arr[], int dep[], int n) {
    int platforms = 1, result = 1;
    int i = 1, j = 0;
    
    for (i = 1; i < n; i++) {
        platforms = 1;
        
        for (j = 0; j < i; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'dep[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if ((arr[i] >= arr[j] && arr[i] <= dep[j]) || 
                /* Possible weaknesses found:
                 *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 *  Cannot determine that 'dep[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                (arr[j] >= arr[i] && arr[j] <= dep[i])) {
                platforms++;
            }
        }
        
        if (platforms > result) {
            result = platforms;
        }
    }
    
    return result;
}

int main() {
    int arr[] = {900, 940, 950, 1100, 1500, 1800};
    int dep[] = {910, 1200, 1120, 1130, 1900, 2000};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Minimum number of platforms required: %d\n", findMinPlatforms(arr, dep, n));
    
    return 0;
}