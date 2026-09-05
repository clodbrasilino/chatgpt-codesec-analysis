#include <stdio.h>
#include <stdlib.h>

void merge(int *array, int *left, int left_size, int *right, int right_size) {
    int i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            array[k++] = left[i++];
        } else {
            array[k++] = right[j++];
        }
    }

    while (i < left_size) {
        array[k++] = left[i++];
    }

    while (j < right_size) {
        array[k++] = right[j++];
    }
}

void merge_sort(int *array, int size) {
    if (size < 2) {
        return;
    }

    int mid = size / 2;
    int *left = (int *)malloc(mid * sizeof(int));
    int *right = (int *)malloc((size - mid) * sizeof(int));

    if (!left || !right) {
        free(left);
        free(right);
        return;
    }

    for (int i = 0; i < mid; i++) {
        left[i] = array[i];
    }

    for (int i = mid; i < size; i++) {
        right[i - mid] = array[i];
    }

    merge_sort(left, mid);
    merge_sort(right, size - mid);
    merge(array, left, mid, right, size - mid);

    free(left);
    free(right);
}

int main(void) {
    int array[] = {38, 27, 43, 3, 9, 82, 10};
    int size = sizeof(array) / sizeof(array[0]);

    merge_sort(array, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}