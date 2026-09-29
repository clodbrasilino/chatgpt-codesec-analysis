#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected [10, 20, 84], got <no output>
  *  test case 2 failed: expected [8, 6, 4], got <no output>
  *  test case 0 failed: expected [2, 4, 6, 8, 10], got <no output>
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
    size_t size = 0;
    size_t capacity = 16;
    int* array = (int*)malloc(capacity * sizeof(int));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    long long num = 0;
    int sign = 1;
    int in_num = 0;
    int c;

    while ((c = getchar()) != EOF) {
        if (isdigit(c)) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 6666666666666666666 * 10 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:721,execs:98,op:havoc,rep:3)
             * UBSan: signed integer overflow: 4444444444444444444 * 10 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:561,execs:79,op:havoc,rep:8)
             */
            num = num * 10 + (c - '0');
            in_num = 1;
        } else if (c == '-') {
            sign = -1;
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
                array[size++] = (int)(num * sign);
                in_num = 0;
                num = 0;
                sign = 1;
            } else {
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
        array[size++] = (int)(num * sign);
    }

    size_t out_size = 0;
    int* even_array = filter_even_numbers(array, size, &out_size);

    printf("[");
    for (size_t i = 0; i < out_size; ++i) {
        printf("%d", even_array[i]);
        if (i < out_size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    free(even_array);
    free(array);

    return EXIT_SUCCESS;
}