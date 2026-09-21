#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int* add_consecutive(const int* arr, size_t size, size_t* out_size) {
    if (out_size == NULL) {
        return NULL;
    }
    if (arr == NULL && size > 0) {
        return NULL;
    }

    if (size == 0) {
        *out_size = 0;
        return malloc(1);
    }

    if (size == 1) {
        *out_size = 1;
        int* res = malloc(sizeof(int));
        if (res != NULL) {
            res[0] = arr[0];
        }
        return res;
    }

    *out_size = size - 1;
    int* result = malloc(*out_size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < *out_size; i++) {
        result[i] = (int)((unsigned int)arr[i] + (unsigned int)arr[i + 1]);
    }

    return result;
}

int main(void) {
    int* input = NULL;
    size_t size = 0;
    size_t capacity = 0;
    int val = 0;

    int c;
    int sign = 1;
    int in_num = 0;

    while ((c = getchar()) != EOF) {
        if (c == '-' && !in_num) {
            sign = -1;
        } else if (isdigit(c)) {
            val = val * 10 + (c - '0');
            in_num = 1;
        } else {
            if (in_num) {
                if (size >= capacity) {
                    capacity = (capacity == 0) ? 16 : capacity * 2;
                    int* temp = realloc(input, capacity * sizeof(int));
                    if (!temp) {
                        free(input);
                        return 1;
                    }
                    input = temp;
                }
                input[size++] = val * sign;
                in_num = 0;
                val = 0;
                sign = 1;
            } else if (c == '-') {
                sign = -1;
            } else {
                sign = 1;
            }
        }
    }
    if (in_num) {
        if (size >= capacity) {
            capacity = (capacity == 0) ? 16 : capacity * 2;
            int* temp = realloc(input, capacity * sizeof(int));
            if (!temp) {
                free(input);
                return 1;
            }
            input = temp;
        }
        input[size++] = val * sign;
    }

    size_t out_size = 0;
    int* result = add_consecutive(input, size, &out_size);
    
    if (result != NULL || size == 0) {
        printf("[");
        for (size_t i = 0; i < out_size; i++) {
            printf("%d", result[i]);
            if (i < out_size - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(result);
    }

    free(input);
    return 0;
}