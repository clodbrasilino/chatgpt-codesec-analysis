#include <stdio.h>
#include <stdlib.h>

int countRotations(const int* arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    int min_index = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[min_index]) {
            min_index = i;
        }
    }

    return min_index;
}

int main(void) {
    int capacity = 16;
    int n = 0;
    int* arr = (int*)malloc(capacity * sizeof(int));
    
    if (!arr) {
        return 1;
    }
    
    int val;
    while (scanf("%d", &val) == 1) {
        if (n >= capacity) {
            capacity *= 2;
            int* temp = (int*)realloc(arr, capacity * sizeof(int));
            if (!temp) {
                free(arr);
                return 1;
            }
            arr = temp;
        }
        arr[n++] = val;
    }
    
    int rotations = countRotations(arr, n);
    
    if (rotations != -1) {
        printf("%d\n", rotations);
    }
    
    free(arr);
    return 0;
}