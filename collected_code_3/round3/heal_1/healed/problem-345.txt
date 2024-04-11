#include <stdio.h>
#include <stdlib.h>

void find_difference(int* arr, int size) {
    int* diff = (int*)malloc((size - 1) * sizeof(int));

    if (diff == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    
    for(int i = 0; i < size - 1; i++) {
        diff[i] = arr[i+1] - arr[i];
    }

    printf("Differences between consecutive numbers are: ");
    for(int i = 0; i < size - 1; i++) {
        printf("%d ", diff[i]);
    }

    free(diff);
}

int main() {
    int arr[] = {1, 2, 3, 5, 8, 13, 21};
    int size = sizeof(arr) / sizeof(arr[0]);
    find_difference(arr, size);
    return 0;
}