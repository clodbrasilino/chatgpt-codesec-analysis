#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int* get_even_numbers(const int *input, size_t input_len, size_t *out_len) {
    if (!input || !out_len) {
        return NULL;
    }

    size_t even_count = 0;
    for (size_t i = 0; i < input_len; ++i) {
        if (input[i] % 2 == 0) {
            even_count++;
        }
    }

    *out_len = even_count;
    if (even_count == 0) {
        return NULL;
    }

    int *evens = (int*)malloc(even_count * sizeof(int));
    if (!evens) {
        *out_len = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < input_len; ++i) {
        if (input[i] % 2 == 0) {
            evens[index++] = input[i];
        }
    }

    return evens;
}

int main(void) {
    const int mixed_list[] = {1, 2, 3, 4, 5, 6, 7, -8, 0, 11, 14};
    size_t input_len = sizeof(mixed_list) / sizeof(mixed_list[0]);
    size_t out_len = 0;

    int *even_list = get_even_numbers(mixed_list, input_len, &out_len);

    if (even_list != NULL || out_len == 0) {
        for (size_t i = 0; i < out_len; ++i) {
            printf("%d ", even_list[i]);
        }
        printf("\n");
        free(even_list);
    } else {
        fprintf(stderr, "Memory allocation or processing failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}