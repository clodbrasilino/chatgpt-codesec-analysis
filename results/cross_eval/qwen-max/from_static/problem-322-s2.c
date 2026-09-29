#include <stdio.h>
#include <stdlib.h>

int *find_min_indices(const int *arr, int n, int *return_size) {
    if (n <= 0) return NULL;
    int min_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) min_val = arr[i];
    }
    int *indices = (int *)malloc(n * sizeof(int));
    if (indices == NULL) return NULL;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == min_val) indices[count++] = i;
    }
    *return_size = count;
    int *result = (int *)realloc(indices, count * sizeof(int));
    if (result == NULL) {
        free(indices);
        return NULL;
    }
    return result;
}

int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int return_size;
    int *min_indices = find_min_indices(arr, n, &return_size);
    if (min_indices != NULL) {
        for (int i = 0; i < return_size; i++) {
            printf("%d ", min_indices[i]);
        }
        free(min_indices);
    } else {
        printf("Error: Memory allocation failed\n");
    }
    return 0;
}