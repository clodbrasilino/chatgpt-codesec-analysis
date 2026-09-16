#include <stdio.h>
#include <stdlib.h>

int find_sum_of_non_repeated(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0;
    }

    int sum = 0;
    for (size_t i = 0; i < size; ++i) {
        int count = 0;
        for (size_t j = 0; j < size; ++j) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count == 1) {
            sum += arr[i];
        }
    }

    return sum;
}

int main(void) {
    int arr[] = {1, 2, 3, 1, 4, 2, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int result = find_sum_of_non_repeated(arr, size);

    printf("%d\n", result);

    return 0;
}