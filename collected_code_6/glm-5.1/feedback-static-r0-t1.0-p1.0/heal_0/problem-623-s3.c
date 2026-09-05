#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

int *calculate_powers(const int *array, size_t length, int n) {
    if (array == NULL || length == 0) {
        errno = EINVAL;
        return NULL;
    }

    int *result = (int *)malloc(length * sizeof(int));
    if (result == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    if (n < 0) {
        for (size_t i = 0; i < length; i++) {
            if (array[i] == 0) {
                free(result);
                errno = EDOM;
                return NULL;
            }
            result[i] = (int)round(pow((double)array[i], (double)n));
        }
    } else {
        for (size_t i = 0; i < length; i++) {
            result[i] = (int)round(pow((double)array[i], (double)n));
        }
    }

    return result;
}

int main(void) {
    int arr[] = {2, -3, 0, 5};
    size_t len = sizeof(arr) / sizeof(arr[0]);
    int n = 3;

    int *res = calculate_powers(arr, len, n);
    if (res == NULL) {
        perror("calculate_powers failed");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < len; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    free(res);

    return EXIT_SUCCESS;
}