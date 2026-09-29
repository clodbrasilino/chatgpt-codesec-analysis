#include <stdio.h>
#include <stdlib.h>

int* find_even_numbers(const int* mixed_list, size_t length, size_t* out_length) {
    if (mixed_list == NULL || out_length == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < length; i++) {
        if (mixed_list[i] % 2 == 0) {
            count++;
        }
    }

    *out_length = count;

    if (count == 0) {
        return NULL;
    }

    int* even_list = (int*)malloc(count * sizeof(int));
    if (even_list == NULL) {
        *out_length = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < length; i++) {
        if (mixed_list[i] % 2 == 0) {
            even_list[index++] = mixed_list[i];
        }
    }

    return even_list;
}

int main(void) {
    int mixed_list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -2, -3};
    size_t length = sizeof(mixed_list) / sizeof(mixed_list[0]);
    size_t out_length = 0;

    int* even_numbers = find_even_numbers(mixed_list, length, &out_length);

    if (even_numbers != NULL || out_length == 0) {
        for (size_t i = 0; i < out_length; i++) {
            printf("%d ", even_numbers[i]);
        }
        printf("\n");
        
        free(even_numbers);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}