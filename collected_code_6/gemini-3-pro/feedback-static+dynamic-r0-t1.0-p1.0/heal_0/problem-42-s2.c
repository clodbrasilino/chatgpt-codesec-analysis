#include <stdio.h>
#include <stdlib.h>

int sum_of_repeated_elements(const int* array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }

    int sum = 0;
    int* counted = (int*)calloc(size, sizeof(int));
    if (counted == NULL) {
        return 0;
    }

    for (size_t i = 0; i < size; i++) {
        if (counted[i] != 0) {
            continue;
        }

        int is_repeated = 0;
        for (size_t j = i + 1; j < size; j++) {
            if (array[i] == array[j]) {
                is_repeated = 1;
                counted[j] = 1;
            }
        }

        if (is_repeated) {
            sum += array[i];
        }
    }

    free(counted);
    counted = NULL;
    
    return sum;
}

int main(void) {
    int arr[] = {1, 2, 3, 2, 4, 3, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int result = sum_of_repeated_elements(arr, size);
    printf("%d\n", result);

    return 0;
}