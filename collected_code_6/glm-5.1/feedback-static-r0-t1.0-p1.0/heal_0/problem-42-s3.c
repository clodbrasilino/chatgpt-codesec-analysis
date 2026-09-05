#include <stdio.h>
#include <stdlib.h>

int sum_of_repeated(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }

    int *seen = (int *)malloc(size * sizeof(int));
    if (seen == NULL) {
        return 0;
    }

    int *counted_duplicates = (int *)malloc(size * sizeof(int));
    if (counted_duplicates == NULL) {
        free(seen);
        return 0;
    }

    size_t seen_size = 0;
    size_t counted_size = 0;
    int sum = 0;

    for (size_t i = 0; i < size; i++) {
        int is_seen = 0;
        for (size_t j = 0; j < seen_size; j++) {
            if (seen[j] == array[i]) {
                is_seen = 1;
                break;
            }
        }

        if (!is_seen) {
            seen[seen_size++] = array[i];
        } else {
            int is_counted = 0;
            for (size_t k = 0; k < counted_size; k++) {
                if (counted_duplicates[k] == array[i]) {
                    is_counted = 1;
                    break;
                }
            }

            if (!is_counted) {
                counted_duplicates[counted_size++] = array[i];
                sum += array[i];
            }
        }
    }

    free(seen);
    free(counted_duplicates);

    return sum;
}

int main(void) {
    int arr[] = {4, 2, 5, 2, 3, 4, 4, 1, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int result = sum_of_repeated(arr, size);
    printf("%d\n", result);

    return 0;
}