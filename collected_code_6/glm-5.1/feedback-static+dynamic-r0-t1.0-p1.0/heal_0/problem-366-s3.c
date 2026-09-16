#include <stdio.h>
#include <stdlib.h>

int largest_product(int *arr, int size) {
    if (size < 2) {
        return 0;
    }

    int max_product = arr[0] * arr[1];

    for (int i = 1; i < size - 1; i++) {
        int current_product = arr[i] * arr[i + 1];
        if (current_product > max_product) {
            max_product = current_product;
        }
    }

    return max_product;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return EXIT_FAILURE;
    }

    int size = argc - 1;
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    int result = largest_product(arr, size);

    printf("%d\n", result);

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}