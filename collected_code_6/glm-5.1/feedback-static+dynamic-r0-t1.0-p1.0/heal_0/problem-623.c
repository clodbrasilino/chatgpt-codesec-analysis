#include <stdio.h>
#include <stdlib.h>

int *power_elements(const int *arr, size_t size, int n) {
    if (arr == NULL || size == 0) {
        return NULL;
    }

    int *result = (int *)malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        long long val = 1;
        int abs_n = n < 0 ? -n : n;
        for (int j = 0; j < abs_n; j++) {
            val *= arr[i];
            if (val > 2147483647 || val < -2147483648) {
                free(result);
                return NULL;
            }
        }
        if (n < 0) {
            if (val == 0) {
                free(result);
                return NULL;
            }
            result[i] = 0;
        } else {
            result[i] = (int)val;
        }
    }

    return result;
}

int main(void) {
    int arr[] = {2, 3, 4, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int n = 3;

    int *result = power_elements(arr, size, n);
    if (result == NULL) {
        return 1;
    }

    for (size_t i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);

    return 0;
}