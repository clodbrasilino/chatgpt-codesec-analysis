#include <stdio.h>
#include <stdlib.h>

int* remove_odd_numbers(const int* input_list, size_t input_size, size_t* output_size) {
    if (input_list == NULL || output_size == NULL) {
        if (output_size != NULL) {
            *output_size = 0;
        }
        return NULL;
    }

    size_t even_count = 0;
    for (size_t i = 0; i < input_size; ++i) {
        if (input_list[i] % 2 == 0) {
            even_count++;
        }
    }

    if (even_count == 0) {
        *output_size = 0;
        return NULL;
    }

    int* output_list = (int*)malloc(even_count * sizeof(int));
    if (output_list == NULL) {
        *output_size = 0;
        return NULL;
    }

    size_t output_index = 0;
    for (size_t i = 0; i < input_size; ++i) {
        if (input_list[i] % 2 == 0) {
            output_list[output_index++] = input_list[i];
        }
    }

    *output_size = even_count;
    return output_list;
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t input_size = sizeof(list) / sizeof(list[0]);
    size_t output_size = 0;

    int* filtered_list = remove_odd_numbers(list, input_size, &output_size);

    if (filtered_list != NULL) {
        for (size_t i = 0; i < output_size; ++i) {
            printf("%d ", filtered_list[i]);
        }
        printf("\n");
        free(filtered_list);
        filtered_list = NULL;
    } else {
        printf("No even numbers found or allocation failed.\n");
    }

    return 0;
}