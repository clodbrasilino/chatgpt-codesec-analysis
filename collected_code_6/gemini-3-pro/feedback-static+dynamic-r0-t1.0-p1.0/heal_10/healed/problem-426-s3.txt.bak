#include <stdio.h>
#include <stdlib.h>

int* filter_odd_numbers(const int* array, size_t length, size_t* out_length) {
    if (array == NULL || length == 0 || out_length == NULL) {
        if (out_length) {
            *out_length = 0;
        }
        return NULL;
    }

    size_t odd_count = 0;
    for (size_t i = 0; i < length; i++) {
        if (array[i] % 2 != 0) {
            odd_count++;
        }
    }

    if (odd_count == 0) {
        *out_length = 0;
        return NULL;
    }

    int* odd_array = (int*)malloc(odd_count * sizeof(int));
    if (odd_array == NULL) {
        *out_length = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < length; i++) {
        if (array[i] % 2 != 0) {
            odd_array[index++] = array[i];
        }
    }

    *out_length = odd_count;
    return odd_array;
}

int main(int argc, const char *const argv[]) {
    int* numbers = NULL;
    size_t length = 0;
    size_t capacity = 0;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (length >= capacity) {
                capacity = capacity == 0 ? 16 : capacity * 2;
                int* temp = (int*)realloc(numbers, capacity * sizeof(int));
                if (!temp) {
                    free(numbers);
                    return 1;
                }
                numbers = temp;
            }
            numbers[length++] = atoi(argv[i]);
        }
    } else {
        int num;
        while (1) {
            int res = scanf("%d", &num);
            if (res == 1) {
                if (length >= capacity) {
                    capacity = capacity == 0 ? 16 : capacity * 2;
                    int* temp = (int*)realloc(numbers, capacity * sizeof(int));
                    if (!temp) {
                        free(numbers);
                        return 1;
                    }
                    numbers = temp;
                }
                numbers[length++] = num;
            } else if (res == EOF) {
                break;
            } else {
                int c = getchar();
                if (c == EOF) {
                    break;
                }
            }
        }
    }

    size_t out_length = 0;
    int* odd_numbers = filter_odd_numbers(numbers, length, &out_length);

    printf("[");
    if (odd_numbers != NULL && out_length > 0) {
        for (size_t i = 0; i < out_length; i++) {
            printf("%d%s", odd_numbers[i], i < out_length - 1 ? ", " : "");
        }
        free(odd_numbers);
    }
    printf("]\n");
    fflush(stdout);

    free(numbers);
    return 0;
}