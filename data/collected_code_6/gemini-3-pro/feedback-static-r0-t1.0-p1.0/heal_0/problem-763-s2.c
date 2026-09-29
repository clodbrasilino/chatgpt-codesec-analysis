#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int compare(const void *a, const void *b) {
    int int_a = *((int *)a);
    int int_b = *((int *)b);

    if (int_a == int_b) return 0;
    else if (int_a < int_b) return -1;
    else return 1;
}

int find_min_difference(int *arr, size_t size) {
    if (arr == NULL || size < 2) {
        return -1; 
    }

    qsort(arr, size, sizeof(int), compare);

    int min_diff = INT_MAX;

    for (size_t i = 1; i < size; ++i) {
        int diff = arr[i] - arr[i - 1];
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    return min_diff;
}

int main(void) {
    int arr[] = {1, 5, 3, 19, 18, 25};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int result = find_min_difference(arr, size);

    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Invalid input or insufficient elements.\n");
    }

    return 0;
}