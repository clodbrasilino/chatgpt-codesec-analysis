#include <stdio.h>
#include <stdlib.h>

int* find_max_indexes(int* arr, int size, int* output_size) {
    int i;
    int max = arr[0];
    for (i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    *output_size = 0;
    for (i = 0; i < size; i++) {
        if (arr[i] == max) {
            (*output_size)++;
        }
    }

    int* max_indexes = (int*) malloc((*output_size) * sizeof(int));
    if (max_indexes == NULL) {
        *output_size = -1;
        return NULL;
    }

    int j = 0;
    for (i = 0; i < size; i++) {
        if (arr[i] == max) {
            max_indexes[j++] = i;
        }
    }

    return max_indexes;
}


int main() {
    int arr[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);

    int indexes_size;
    int* max_indexes = find_max_indexes(arr, size, &indexes_size);

    if (!max_indexes) {
        printf("Memory allocation failed");
        return 1;
    }

    printf("Max value found at indexes: ");
    for (int i = 0; i < indexes_size; i++) {
        printf("%d ", max_indexes[i]);
    }

    free(max_indexes);

    return 0;
}
