#include <stdio.h>
#include <stdlib.h>

int* filter_even_numbers(const int* array, size_t size, size_t* out_size) {
    if (array == NULL || out_size == NULL) {
        if (out_size != NULL) {
            *out_size = 0;
        }
        return NULL;
    }

    size_t even_count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] % 2 == 0) {
            even_count++;
        }
    }

    *out_size = even_count;
    if (even_count == 0) {
        return NULL;
    }

    int* even_array = (int*)malloc(even_count * sizeof(int));
    if (even_array == NULL) {
        *out_size = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] % 2 == 0) {
            even_array[index++] = array[i];
        }
    }

    return even_array;
}

int main(void) {
    int* array = NULL;
    size_t size = 0;
    size_t capacity = 16;
    int num;

    array = (int*)malloc(capacity * sizeof(int));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    while (1) {
        int ret = scanf("%d", &num);
        if (ret == 1) {
            if (size >= capacity) {
                capacity *= 2;
                int* temp = (int*)realloc(array, capacity * sizeof(int));
                if (temp == NULL) {
                    free(array);
                    return EXIT_FAILURE;
                }
                array = temp;
            }
            array[size++] = num;
        } else {
            int c = getchar();
            if (c == EOF) {
                break;
            }
        }
    }

    size_t out_size = 0;
    int* even_array = filter_even_numbers(array, size, &out_size);

    printf("[");
    for (size_t i = 0; i < out_size; ++i) {
        printf("%d%s", even_array[i], (i < out_size - 1) ? ", " : "");
    }
    printf("]\n");

    if (even_array != NULL) {
        free(even_array);
    }
    free(array);
    return EXIT_SUCCESS;
}