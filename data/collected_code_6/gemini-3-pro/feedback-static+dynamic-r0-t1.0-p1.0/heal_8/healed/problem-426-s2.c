#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int* filter_odd_numbers(const int* arr, size_t size, size_t* out_size) {
    if (arr == NULL || out_size == NULL) {
        if (out_size != NULL) {
            *out_size = 0;
        }
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] % 2 != 0) {
            count++;
        }
    }

    *out_size = count;

    if (count == 0) {
        return NULL;
    }

    int* odd_arr = (int*)malloc(count * sizeof(int));
    if (odd_arr == NULL) {
        *out_size = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] % 2 != 0) {
            odd_arr[index++] = arr[i];
        }
    }

    return odd_arr;
}

int main(int argc, const char *argv[]) {
    int arr[10000];
    size_t size = 0;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (size < 10000) {
                arr[size++] = (int)strtol(argv[i], NULL, 10);
            }
        }
    } else {
        int val;
        while (scanf("%d", &val) == 1) {
            if (size < 10000) {
                arr[size++] = val;
            }
        }
    }

    size_t out_size = 0;
    int* odd_arr = filter_odd_numbers(arr, size, &out_size);

    printf("[");
    for (size_t i = 0; i < out_size; ++i) {
        printf("%d", odd_arr[i]);
        if (i < out_size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    fflush(stdout);

    if (odd_arr != NULL) {
        free(odd_arr);
    }

    return EXIT_SUCCESS;
}