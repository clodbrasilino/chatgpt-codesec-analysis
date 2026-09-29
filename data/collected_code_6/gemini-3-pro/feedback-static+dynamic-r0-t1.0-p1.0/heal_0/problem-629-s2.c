#include <stdio.h>
#include <stdlib.h>

int* find_even_numbers(const int *input_list, size_t input_size, size_t *out_size) {
    if (input_list == NULL || out_size == NULL) {
        return NULL;
    }

    size_t even_count = 0;
    for (size_t i = 0; i < input_size; i++) {
        if (input_list[i] % 2 == 0) {
            even_count++;
        }
    }

    *out_size = even_count;

    if (even_count == 0) {
        return NULL;
    }

    int *even_list = (int*)malloc(even_count * sizeof(int));
    if (even_list == NULL) {
        *out_size = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < input_size; i++) {
        if (input_list[i] % 2 == 0) {
            even_list[index++] = input_list[i];
        }
    }

    return even_list;
}

int main(void) {
    int mixed_list[] = {1, -2, 3, 4, 15, 16, 27, 42, 99, 100};
    size_t input_size = sizeof(mixed_list) / sizeof(mixed_list[0]);
    size_t even_size = 0;

    int *even_list = find_even_numbers(mixed_list, input_size, &even_size);

    if (even_list != NULL && even_size > 0) {
        for (size_t i = 0; i < even_size; i++) {
            printf("%d ", even_list[i]);
        }
        printf("\n");
        
        free(even_list);
        even_list = NULL;
    }

    return 0;
}