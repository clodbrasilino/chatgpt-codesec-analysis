#include <stdio.h>
#include <stdlib.h>

int* find_min_indices(int *arr, int length, int *return_size) {
    if (length == 0 || arr == NULL) {
        *return_size = 0;
        return NULL;
    }
    
    int min_value = arr[0];
    for (int i = 1; i < length; ++i) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }

    int count = 0;
    for (int i = 0; i < length; ++i) {
        if (arr[i] == min_value) {
            ++count;
        }
    }

    int *indices = (int *) malloc(count * sizeof(int));
    if (indices == NULL) {
        *return_size = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < length; ++i) {
        if (arr[i] == min_value) {
            indices[index++] = i;
        }
    }

    *return_size = count;
    return indices;
}

int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int length = sizeof(arr) / sizeof(arr[0]);
    int return_size;

    int *min_indices = find_min_indices(arr, length, &return_size);
    
    if (min_indices != NULL) {
        for (int i = 0; i < return_size; ++i) {
            printf("%d ", min_indices[i]);
        }
        free(min_indices);
    } else {
        printf("No minimum values found or invalid input.\n");
    }

    return 0;
}