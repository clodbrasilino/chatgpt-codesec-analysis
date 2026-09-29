#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
    size_t size = 0;
    size_t capacity = 16;
    int* array = (int*)malloc(capacity * sizeof(int));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    int num = 0;
    int sign = 1;
    int in_num = 0;
    int c;

    while ((c = getchar()) != EOF) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
            in_num = 1;
        } else {
            if (in_num) {
                if (size >= capacity) {
                    capacity *= 2;
                    int* temp = (int*)realloc(array, capacity * sizeof(int));
                    if (temp == NULL) {
                        free(array);
                        return EXIT_FAILURE;
                    }
                    array = temp;
                }
                array[size++] = num * sign;
                in_num = 0;
                num = 0;
                sign = 1;
            }
            if (c == '-') {
                sign = -1;
            } else if (c == '\n') {
                break;
            } else if (!isspace(c) && c != '[' && c != ']' && c != ',') {
                sign = 1;
            }
        }
    }

    if (in_num) {
        if (size >= capacity) {
            capacity *= 2;
            int* temp = (int*)realloc(array, capacity * sizeof(int));
            if (temp == NULL) {
                free(array);
                return EXIT_FAILURE;
            }
            array = temp;
        }
        array[size++] = num * sign;
    }

    size_t out_size = 0;
    int* even_array = filter_even