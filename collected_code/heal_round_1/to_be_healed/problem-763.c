#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; did you forget to '#include <limits.h>'?
  */

int minDifference(int arr[], int size) {
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' undeclared (first use in this function)
     */
    int minDiff = INT_MAX;

    for (int i = 0; i < size-1; i++) {
        for (int j = i+1; j < size; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            int diff = abs(arr[i] - arr[j]);
            if (diff < minDiff)
                minDiff = diff;
        }
    }

    return minDiff;
}

int main() {
    int arr[] = {3, 7, 1, 9, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = minDifference(arr, size);
    
    printf("Minimum difference between any two elements: %d\n", result);
    
    return 0;
}