#include <stdio.h>
#include <stdlib.h>

void nth_items(int *list, int size, int n, int *result, int *resultSize) {
    int count = 0;
    for (int i = n - 1; i < size; i += n) {
        result[count++] = list[i];
    }
    *resultSize = count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int n = 3;
    int resultSize;
    int *result = (int *)malloc(size * sizeof(int));
    
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    nth_items(arr, size, n, result, &resultSize);
    
    for (int i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);
    }
    
    free(result);
    return 0;
}