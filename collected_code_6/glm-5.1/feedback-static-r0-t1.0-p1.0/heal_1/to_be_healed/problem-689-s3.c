#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int min_jumps(int *arr, int n) {
    if (n <= 0) {
        return -1;
    }
    if (n == 1) {
        return 0;
    }
    if (arr[0] == 0) {
        return -1;
    }
    
    int *jumps = (int *)malloc(n * sizeof(int));
    if (jumps == NULL) {
        return -1;
    }
    
    jumps[0] = 0;
    for (int i = 1; i < n; i++) {
        jumps[i] = INT_MAX;
        for (int j = 0; j < i; j++) {
            if (jumps[j] != INT_MAX && i <= j + arr[j]) {
                if (jumps[j] + 1 < jumps[i]) {
                    jumps[i] = jumps[j] + 1;
                }
                break;
            }
        }
        if (jumps[i] == INT_MAX) {
            free(jumps);
            return -1;
        }
    }
    
    int result = jumps[n - 1];
    free(jumps);
    return result;
}

int main() {
    int arr1[] = {2, 3, 1, 1, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int res1 = min_jumps(arr1, n1);
    printf("%d\n", res1);
    
    int arr2[] = {1, 1, 1, 1, 1};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int res2 = min_jumps(arr2, n2);
    printf("%d\n", res2);

    int arr3[] = {0, 1, 1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int res3 = min_jumps(arr3, n3);
    printf("%d\n", res3);

    return 0;
}