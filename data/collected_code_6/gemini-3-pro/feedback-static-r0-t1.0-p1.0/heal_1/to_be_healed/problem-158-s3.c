#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int findMax(int arr[], int n) {
    int max = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int minOperations(int arr[], int n) {
    if (n == 0) return 0;
    
    int maxVal = findMax(arr, n);
    int operations = 0;
    
    for (int i = 0; i < n; i++) {
        operations += (maxVal - arr[i]);
    }
    
    return operations;
}

int main() {
    int arr[] = {1, 5, 2, 4, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int result = minOperations(arr, n);
    
    printf("%d\n", result);
    
    return 0;
}