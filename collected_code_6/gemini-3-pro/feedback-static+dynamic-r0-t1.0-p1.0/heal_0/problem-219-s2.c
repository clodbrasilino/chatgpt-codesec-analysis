#include <stdio.h>
#include <stdlib.h>

void sort_array(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void extract_max_min_k(const int *tuple, int size, int k, int *max_k, int *min_k) {
    if (tuple == NULL || max_k == NULL || min_k == NULL || k <= 0 || k > size) {
        return;
    }

    int *temp_iter = (int *)malloc(size * sizeof(int));
    if (temp_iter == NULL) {
        return;
    }

    for (int i = 0; i < size; i++) {
        temp_iter[i] = tuple[i];
    }

    sort_array(temp_iter, size);

    for (int i = 0; i < k; i++) {
        min_k[i] = temp_iter[i];
        max_k[i] = temp_iter[size - i - 1];
    }

    free(temp_iter);
}

int main() {
    int tuple[] = {5, 20, 3, 7, 6, 8, 1, 9, 15, 2};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    int k = 3;

    int *max_k = (int *)malloc(k * sizeof(int));
    int *min_k = (int *)malloc(k * sizeof(int));

    if (max_k == NULL || min_k == NULL) {
        if (max_k != NULL) free(max_k);
        if (min_k != NULL) free(min_k);
        return 1;
    }

    extract_max_min_k(tuple, size, k, max_k, min_k);

    for (int i = 0; i < k; i++) {
        printf("%d ", min_k[i]);
    }
    printf("\n");

    for (int i = 0; i < k; i++) {
        printf("%d ", max_k[i]);
    }
    printf("\n");

    free(max_k);
    free(min_k);

    return 0;
}