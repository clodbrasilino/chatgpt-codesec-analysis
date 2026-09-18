#include <stdio.h>
#include <stdlib.h>

int countRotations(const int arr[], int n) {
    if (n == 0) return 0;
    int min_idx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[min_idx]) {
            min_idx = i;
        }
    }
    return min_idx;
}

int main(void) {
    int n;
    if (scanf("%d", &n) == 1) {
        int *arr = (int *)malloc(n * sizeof(int));
        if (arr) {
            for (int i = 0; i < n; i++) {
                scanf("%d", &arr[i]);
            }
            
            int rotations = countRotations(arr, n);
            printf("%d\n", rotations);
            
            free(arr);
        }
    }
    return 0;
}