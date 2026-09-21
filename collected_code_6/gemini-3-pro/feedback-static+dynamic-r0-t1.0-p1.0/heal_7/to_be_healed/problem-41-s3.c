#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [2, 4, 6, 8, 10], got <no output>
  *  test case 1 failed: expected [10, 20, 84], got <no output>
  *  test case 2 failed: expected [8, 6, 4], got <no output>
  */

int* filter_even_numbers(const int* array, size_t size, size_t* out_size) {
    if (array == NULL || out_size == NULL) {
        if (out_size) *out_size = 0;
        return NULL;
    }
    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] % 2 == 0) {
            count++;
        }
    }
    *out_size = count;
    if (count == 0) {
        return NULL;
    }
    int* even_array = (int*)malloc(count * sizeof(int));
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
    int capacity = 16;
    int size = 0;
    int* numbers = (int*)malloc(capacity * sizeof(int));
    if (numbers == NULL) {
        return 1;
    }

    int val;
    int res;
    while ((res = scanf("%d", &val)) != EOF) {
        if (res == 1) {
            if (size >= capacity) {
                capacity *= 2;
                int* temp = (int*)realloc(numbers, capacity * sizeof(int));
                if (temp == NULL) {
                    free(numbers);
                    return 1;
                }
                numbers = temp;
            }
            numbers[size++] = val;
        } else {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            if (fgetc(stdin) == EOF) {
                break;
            }
        }
    }

    size_t even_size = 0;
    int* even_numbers = filter_even_numbers(numbers, (size_t)size, &even_size);

    if (even_size > 0 && even_numbers != NULL) {
        printf("[%d", even_numbers[0]);
        for (size_t i = 1; i < even_size; ++i) {
            printf(", %d", even_numbers[i]);
        }
        printf("]\n");
        free(even_numbers);
    } else {
        printf("[]\n");
    }

    free(numbers);
    return 0;
}