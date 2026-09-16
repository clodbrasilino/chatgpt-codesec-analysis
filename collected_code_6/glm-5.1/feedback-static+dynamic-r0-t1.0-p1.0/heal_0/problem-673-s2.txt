#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long list_to_single_int(const int *list, size_t size) {
    long long result = 0;
    if (list == NULL || size == 0) {
        return 0;
    }
    for (size_t i = 0; i < size; i++) {
        if (list[i] < 0) {
            errno = ERANGE;
            return 0;
        }
        if (result > (LLONG_MAX - list[i]) / 10) {
            errno = ERANGE;
            return 0;
        }
        result = result * 10 + list[i];
    }
    return result;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    long long res1 = list_to_single_int(arr1, size1);
    if (errno == ERANGE) {
        perror("Conversion failed");
        return EXIT_FAILURE;
    }
    printf("%lld\n", res1);

    int arr2[] = {9, 2, 2, 3, 3, 7, 2, 0, 3, 6, 8, 5, 4, 7, 7, 5, 8, 0, 8};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    errno = 0;
    long long res2 = list_to_single_int(arr2, size2);
    if (errno == ERANGE) {
        perror("Conversion failed");
        return EXIT_FAILURE;
    }
    printf("%lld\n", res2);

    return EXIT_SUCCESS;
}