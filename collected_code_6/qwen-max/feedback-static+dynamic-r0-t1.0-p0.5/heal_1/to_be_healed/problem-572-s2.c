#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void remove_duplicates(int *arr, int *size) {
    if (*size <= 1) return;

    qsort(arr, *size, sizeof(int), compare);

    int *new_arr = (int *)malloc(*size * sizeof(int));
    if (!new_arr) exit(EXIT_FAILURE);

    int new_size = 0;
    for (int i = 0; i < *size; ++i) {
        if (i == 0 || arr[i] != arr[i - 1]) {
            new_arr[new_size++] = arr[i];
        }
    }

    /* Possible weaknesses found:
     * ASan: attempting
     */
    free(arr);
    *arr = *new_arr;
    *size = new_size;
    free(new_arr);
}

int main() {
    int arr[] = {5, 4, 5, 3, 2, 3, 4, 1};
    int size = sizeof(arr) / sizeof(arr[0]);

    remove_duplicates(arr, &size);

    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    /* Possible weaknesses found:
     *  Deallocation of an auto-variable results in undefined behaviour. [autovarInvalidDeallocation]
     */
    free(arr);
    return 0;
}