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
    int num;

    while (size < 10000) {
        if (scanf("%d", &num) == 1) {
            arr[size++] = num;
        } else {
            int c = getchar();
            if (c == EOF) {
                break;
            }
        }
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

    return 0;
}