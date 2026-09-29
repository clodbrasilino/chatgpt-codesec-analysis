#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int countGlobalInversions(int *arr, int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                count++;
            }
        }
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int countLocalInversions(int *arr, int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            count++;
        }
    }
    return count;
}

int areInversionsSame(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    
    int globalInversions = countGlobalInversions(arr, n);
    int localInversions = countLocalInversions(arr, n);
    
    return globalInversions == localInversions;
}

int main() {
    int arr[] = {1, 0, 2, 4, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    if (areInversionsSame(arr, n)) {
        printf("The counts of global and local inversions are the same.\n");
    } else {
        printf("The counts of global and local inversions are different.\n");
    }
    
    return 0;
}