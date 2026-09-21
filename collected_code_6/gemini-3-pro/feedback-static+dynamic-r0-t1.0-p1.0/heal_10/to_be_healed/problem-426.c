#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected [5, 7, 9, 3], got <no output>
  *  test case 1 failed: expected [45, 67, 93], got <no output>
  *  test case 0 failed: expected [1, 3, 5, 7, 9], got <no output>
  */

int* filter_odd_numbers(const int* array, size_t size, size_t* out_size) {
    if (array == NULL || out_size == NULL) {
        if (out_size) {
            *out_size = 0;
        }
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] % 2 != 0) {
            count++;
        }
    }

    *out_size = count;

    if (count == 0) {
        return NULL;
    }

    int* odd_array = (int*)malloc(count * sizeof(int));
    if (odd_array == NULL) {
        *out_size = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] % 2 != 0) {
            odd_array[index++] = array[i];
        }
    }

    return odd_array;
}

int main(int argc, const char *argv[]) {
    int cap = 10;
    int size = 0;
    int* numbers = (int*)malloc(cap * sizeof(int));
    if (!numbers) return 1;

    int val;
    while (1) {
        int res = scanf("%d", &val);
        if (res == 1) {
            if (size == cap) {
                cap *= 2;
                int* next = (int*)realloc(numbers, cap * sizeof(int));
                if (!next) { 
                    free(numbers); 
                    return 1; 
                }
                numbers = next;
            }
            numbers[size++] = val;
        } else if (res == EOF) {
            break;
        } else {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            getchar();
        }
    }

    size_t out_size = 0;
    int* odd_numbers = filter_odd_numbers(numbers, (size_t)size, &out_size);

    printf("[");
    for (size_t i = 0; i < out_size; ++i) {
        printf("%d%s", odd_numbers[i], i == out_size - 1 ? "" : ", ");
    }
    printf("]\n");

    free(odd_numbers);
    free(numbers);

    return 0;
}