#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 1
  *  test case 2 failed: expected 3, got 1
  */

int countRotations(const int* arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }
    
    int min_val = arr[0];
    int min_idx = 0;
    
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
            min_idx = i;
        }
    }
    
    return min_idx;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }
    
    int* arr = (int*)malloc(n * sizeof(int));
    if (!arr) {
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }
    
    int rotations = countRotations(arr, n);
    
    if (rotations != -1) {
        printf("%d\n", rotations);
    }
    
    free(arr);
    return 0;
}