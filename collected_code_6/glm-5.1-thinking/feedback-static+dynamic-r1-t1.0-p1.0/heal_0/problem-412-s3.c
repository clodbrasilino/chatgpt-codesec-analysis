#include <stdio.h>
#include <stdlib.h>

int* remove_odd_numbers(const int* list, size_t length, size_t* out_length) {
    if (list == NULL || out_length == NULL) {
        return NULL;
    }

    *out_length = 0;

    size_t even_count = 0;
    for (size_t i = 0; i < length; ++i) {
        if (list[i] % 2 == 0) {
            even_count++;
        }
    }

    if (even_count == 0) {
        return NULL;
    }

    int* even_list = malloc(even_count * sizeof(int));
    if (even_list == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < length; ++i) {
        if (list[i] % 2 == 0) {
            even_list[j++] = list[i];
        }
    }

    *out_length = even_count;
    return even_list;
}

int main(void) {
    int input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t input_length = sizeof(input) / sizeof(input[0]);
    size_t output_length = 0;

    int* output = remove_odd_numbers(input, input_length, &output_length);

    for (size_t i = 0; i < output_length; ++i) {
        printf("%d ", output[i]);
    }
    printf("\n");

    free(output);

    return EXIT_SUCCESS;
}