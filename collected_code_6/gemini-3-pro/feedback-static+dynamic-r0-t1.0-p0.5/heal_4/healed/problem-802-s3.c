#include <stdio.h>
#include <stdlib.h>

int countRotations(const int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return i + 1;
        }
    }
    return 0;
}

int main(void) {
    int capacity = 16;
    int *arr = (int *)malloc(capacity * sizeof(int));
    int n = 0;
    
    if (arr == NULL) {
        return 1;
    }

    while (scanf("%d", &arr[n]) == 1) {
        n++;
        if (n >= capacity) {
            capacity *= 2;
            int *temp = (int *)realloc(arr, capacity * sizeof(int));
            if (temp == NULL) {
                free(arr);
                return 1;
            }
            arr = temp;
        }
    }
    
    if (n > 0) {
        int rotations = countRotations(arr, n);
        printf("%d\n", rotations);
    }
    
    free(arr);
    return 0;
}