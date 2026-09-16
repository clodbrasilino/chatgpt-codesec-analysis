#include <stdio.h>
#include <stdlib.h>

int *find_positive_ratio(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return NULL;
    }

    int *result = (int *)malloc(2 * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    int positive_count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] > 0) {
            ++positive_count;
        }
    }

    int current_gcd = positive_count;
    int remainder = size;
    while (remainder != 0) {
        int temp = current_gcd;
        current_gcd = remainder;
        remainder = temp % remainder;
    }

    if (current_gcd == 0) {
        result[0] = 0;
        result[1] = 1;
    } else {
        result[0] = positive_count / current_gcd;
        result[1] = (int)(size / current_gcd);
    }

    return result;
}

int main(void) {
    int arr[] = {1, -2, 3, 4, -5, 6};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int *ratio = find_positive_ratio(arr, size);
    if (ratio == NULL) {
        return EXIT_FAILURE;
    }

    printf("%d/%d\n", ratio[0], ratio[1]);
    free(ratio);
    ratio = NULL;

    return EXIT_SUCCESS;
}