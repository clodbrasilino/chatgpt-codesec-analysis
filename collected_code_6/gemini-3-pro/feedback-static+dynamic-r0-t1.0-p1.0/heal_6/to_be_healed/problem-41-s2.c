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
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000003,sig:06,src:000000,time:13119,execs:1150,op:havoc,rep:7; likely memory-safety defect
  */

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
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 888888888 * 10 cannot be represented in type 'int' (AFL crash: id:000005,sig:06,src:000000,time:29707,execs:2491,op:havoc,rep:11)
             * UBSan: signed integer overflow: 333333333 * 10 cannot be represented in type 'int' (AFL crash: id:000006,sig:06,src:000000,time:34196,execs:2703,op:havoc,rep:9)
             * UBSan: signed integer overflow: 444444444 * 10 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000000,time:5858,execs:552,op:havoc,rep:10)
             * UBSan: signed integer overflow: 666666666 * 10 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:694,execs:95,op:havoc,rep:14)
             * UBSan: signed integer overflow: 222022222 * 10 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:3201,execs:307,op:havoc,rep:14)
             */
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