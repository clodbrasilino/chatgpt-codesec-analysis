#include <stdio.h>
#include <stdlib.h>

int* filter_odd_numbers(const int* arr, size_t size, size_t* out_size) {
    if (arr == NULL || out_size == NULL) {
        if (out_size) *out_size = 0;
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

int main(void) {
    int arr[10000];
    size_t size = 0;
    int c;
    long long val = 0;
    int sign = 1;
    int has_val = 0;

    while ((c = getchar()) != EOF && size < 10000) {
        if (c == '-') {
            sign = -1;
        } else if (c >= '0' && c <= '9') {
            val = val * 10 + (c - '0');
            has_val = 1;
        } else {
            if (has_val) {
                arr[size++] = (int)(val * sign);
                has_val = 0;
                val = 0;
            }
            if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
                sign = 1;
            }
        }
    }
    if (has_val && size < 10000) {
        arr[size++] = (int)(val * sign);
    }

    size_t out_size = 0;
    int* odd_arr = filter_odd_numbers(arr, size, &out_size);

    printf("[");
    if (odd_arr != NULL && out_size > 0) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%d", odd_arr[i]);
            if (i < out_size - 1) {
                printf(", ");
            }
        }
        free(odd_arr);
    }
    printf("]\n");
    fflush(stdout);

    return 0;
}