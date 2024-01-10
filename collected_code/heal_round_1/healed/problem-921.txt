#include <stdio.h>

void chunk_tuples(const int *arr, int size, int n) {
    int i;
    for (i = 0; i < size; i += n) {
        int j;
        for (j = i; j < i + n && j < size; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int n = 3;
    
    chunk_tuples(arr, size, n);
    
    return 0;
}