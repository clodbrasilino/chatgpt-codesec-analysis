#include <stdio.h>
#include <stdlib.h>

int sum_non_repeated(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0;
    }

    int *temp = malloc(size * sizeof(int));
    if (temp == NULL) {
        return 0;
    }

    for (size_t i = 0; i < size; i++) {
        temp[i] = arr[i];
    }

    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (temp[i] > temp[j]) {
                int swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
        }
    }

    int sum = 0;
    size_t i = 0;
    while (i < size) {
        if (i + 1 < size && temp[i] == temp[i + 1]) {
            while (i + 1 < size && temp[i] == temp[i + 1]) {
                i++;
            }
            i++;
        } else {
            sum += temp[i];
            i++;
        }
    }

    free(temp);
    return sum;
}

int main(void) {
    int arr[] = {1, 2, 3, 2, 4, 1, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int result = sum_non_repeated(arr, size);

    printf("%d\n", result);

    return 0;
}