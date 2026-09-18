#include <stdio.h>
#include <stdlib.h>

void remove_negatives(int **arr, size_t *size) {
    if (arr == NULL || *arr == NULL || size == NULL) {
        return;
    }

    size_t new_size = 0;
    for (size_t i = 0; i < *size; i++) {
        if ((*arr)[i] >= 0) {
            new_size++;
        }
    }

    if (new_size == 0) {
        free(*arr);
        *arr = NULL;
        *size = 0;
        return;
    }

    int *new_arr = (int *)malloc(new_size * sizeof(int));
    if (new_arr == NULL) {
        return;
    }

    size_t index = 0;
    for (size_t i = 0; i < *size; i++) {
        if ((*arr)[i] >= 0) {
            new_arr[index++] = (*arr)[i];
        }
    }

    free(*arr);
    *arr = new_arr;
    *size = new_size;
}

int main(void) {
    size_t size = 5;
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    arr[0] = 10;
    arr[1] = -5;
    arr[2] = 3;
    arr[3] = -1;
    arr[4] = 7;

    remove_negatives(&arr, &size);

    if (arr != NULL) {
        for (size_t i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        free(arr);
    }

    return 0;
}