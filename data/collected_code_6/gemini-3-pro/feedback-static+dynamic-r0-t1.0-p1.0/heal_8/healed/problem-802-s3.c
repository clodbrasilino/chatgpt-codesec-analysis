#include <stdio.h>
#include <stdlib.h>

int countRotations(const int* arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }
    
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            return i;
        }
    }
    
    return 0;
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