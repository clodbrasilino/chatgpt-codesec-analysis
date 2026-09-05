#include <stdio.h>
#include <stdlib.h>

int find_non_repeated_product(const int *arr, size_t size, long long *result) {
    if (arr == NULL || result == NULL) {
        return -1;
    }
    if (size == 0) {
        *result = 0;
        return 0;
    }

    int *visited = (int *)malloc(size * sizeof(int));
    if (visited == NULL) {
        return -1;
    }

    for (size_t i = 0; i < size; ++i) {
        visited[i] = 0;
    }

    for (size_t i = 0; i < size; ++i) {
        if (visited[i] == 0) {
            size_t count = 1;
            for (size_t j = i + 1; j < size; ++j) {
                if (arr[i] == arr[j]) {
                    count++;
                    visited[j] = 1;
                }
            }
            if (count == 1) {
                *result *= arr[i];
            }
        }
    }

    free(visited);
    return 0;
}

int main(void) {
    int arr[] = {2, 3, 4, 5, 3, 6, 2};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    long long result = 1;

    if (find_non_repeated_product(arr, size, &result) == 0) {
        printf("%lld\n", result);
    } else {
        fprintf(stderr, "Error calculating product\n");
        return 1;
    }

    return 0;
}