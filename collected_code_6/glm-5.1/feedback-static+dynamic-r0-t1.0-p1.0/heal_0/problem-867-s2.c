#include <stdio.h>
#include <stdlib.h>

int min_to_even_sum(int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    int sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += arr[i];
    }

    if (sum % 2 == 0) {
        return 0;
    }

    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    size_t size = (size_t)(argc - 1);
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    int result = min_to_even_sum(arr, size);

    printf("%d\n", result);

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}