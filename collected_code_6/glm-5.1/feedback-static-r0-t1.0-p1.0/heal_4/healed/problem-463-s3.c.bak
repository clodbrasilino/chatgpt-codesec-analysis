#include <stdio.h>
#include <stdlib.h>

int max_product_subarray(const int *arr, int size, int *start, int *end) {
    if (arr == NULL || size <= 0 || start == NULL || end == NULL) {
        return 0;
    }

    int max_ending = arr[0];
    int min_ending = arr[0];
    int global_max = arr[0];
    int curr_start = 0;
    int max_start = 0;
    int max_end = 0;

    for (int i = 1; i < size; i++) {
        if (arr[i] < 0) {
            int temp = max_ending;
            max_ending = min_ending;
            min_ending = temp;
        }

        if (max_ending * arr[i] > arr[i]) {
            max_ending = max_ending * arr[i];
        } else {
            max_ending = arr[i];
            curr_start = i;
        }

        if (min_ending * arr[i] < arr[i]) {
            min_ending = min_ending * arr[i];
        } else {
            min_ending = arr[i];
        }

        if (max_ending > global_max) {
            global_max = max_ending;
            max_start = curr_start;
            max_end = i;
        }
    }

    *start = max_start;
    *end = max_end;
    return global_max;
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        return 1;
    }

    int size = argc - 1;
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    int start = 0;
    int end = 0;
    int max_prod = max_product_subarray(arr, size, &start, &end);

    printf("Maximum Product: %d\n", max_prod);
    printf("Subarray: ");
    for (int i = start; i <= end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    arr = NULL;
    return 0;
}