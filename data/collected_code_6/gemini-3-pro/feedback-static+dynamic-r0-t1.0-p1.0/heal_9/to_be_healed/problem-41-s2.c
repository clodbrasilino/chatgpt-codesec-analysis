#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [2, 4, 6, 8, 10], got <no output>
  *  test case 1 failed: expected [10, 20, 84], got <no output>
  *  test case 2 failed: expected [8, 6, 4], got <no output>
  */

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
    size_t capacity = 10;
    int num;

    array = (int*)malloc(capacity * sizeof(int));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    while (scanf("%d", &num) == 1) {
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
    }

    size_t out_size = 0;
    int* even_array = filter_even_numbers(array, size, &out_size);

    printf("[");
    if (even_array != NULL && out_size > 0) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%d", even_array[i]);
            if (i < out_size - 1) {
                printf(", ");
            }
        }
        free(even_array);
    }
    printf("]\n");

    free(array);
    return EXIT_SUCCESS;
}