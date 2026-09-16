#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

int sum_three_lowest_positive(int *array, size_t size) {
    if (size < 3) {
        return 0;
    }

    int *copy = malloc(size * sizeof(int));
    if (copy == NULL) {
        return 0;
    }

    for (size_t i = 0; i < size; ++i) {
        copy[i] = array[i];
    }

    qsort(copy, size, sizeof(int), compare);

    int sum = 0;
    int count = 0;

    for (size_t i = 0; i < size; ++i) {
        if (copy[i] > 0) {
            sum += copy[i];
            count++;
            if (count == 3) {
                break;
            }
        }
    }

    free(copy);

    if (count < 3) {
        return 0;
    }

    return sum;
}

int main(void) {
    int arr[] = {4, -1, 2, 5, 0, -3, 1, 9};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int result = sum_three_lowest_positive(arr, size);

    printf("%d\n", result);

    return 0;
}