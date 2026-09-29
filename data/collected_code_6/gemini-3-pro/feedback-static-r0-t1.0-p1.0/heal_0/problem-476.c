#include <stdio.h>
#include <limits.h>

int sum_of_min_max(const int *array, size_t size, int *result) {
    if (array == NULL || size == 0 || result == NULL) {
        return -1;
    }

    int min_val = INT_MAX;
    int max_val = INT_MIN;

    for (size_t i = 0; i < size; ++i) {
        if (array[i] < min_val) {
            min_val = array[i];
        }
        if (array[i] > max_val) {
            max_val = array[i];
        }
    }

    if ((max_val > 0 && min_val > INT_MAX - max_val) || 
        (max_val < 0 && min_val < INT_MIN - max_val)) {
        return -1; 
    }

    *result = min_val + max_val;
    return 0;
}

int main(void) {
    int arr[] = { 3, 1, 9, -4, 5, 2, 8 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int sum = 0;

    int status = sum_of_min_max(arr, n, &sum);

    if (status == 0) {
        printf("Sum of min and max: %d\n", sum);
    } else {
        printf("Error calculating sum.\n");
    }

    return 0;
}