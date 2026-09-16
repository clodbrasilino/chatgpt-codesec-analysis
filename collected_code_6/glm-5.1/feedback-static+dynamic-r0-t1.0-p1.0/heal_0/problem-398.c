#include <stdio.h>
#include <stdlib.h>

int sum_of_digits(int n) {
    int sum = 0;
    int abs_n = abs(n);
    while (abs_n > 0) {
        sum += abs_n % 10;
        abs_n /= 10;
    }
    return sum;
}

int *compute_sums(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return NULL;
    }

    int *result = (int *)malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; ++i) {
        result[i] = sum_of_digits(list[i]);
    }

    return result;
}

int main(void) {
    int list[] = {123, 456, -789, 0, 42};
    size_t size = sizeof(list) / sizeof(list[0]);

    int *sums = compute_sums(list, size);
    if (sums == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; ++i) {
        printf("%d ", sums[i]);
    }
    printf("\n");

    free(sums);
    sums = NULL;

    return EXIT_SUCCESS;
}