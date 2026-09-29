#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [2, 4, 6, 8, 10], got <no output>
  *  test case 1 failed: expected [10, 20, 84], got <no output>
  *  test case 2 failed: expected [8, 6, 4], got <no output>
  */

int* filter_even_numbers(const int* array, size_t size, size_t* out_size) {
    if (array == NULL || out_size == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] % 2 == 0) {
            count++;
        }
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

    *out_size = count;
    return even_array;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    /* Possible weaknesses found:
     *  Assignment 'size=sizeof(numbers)/sizeof(numbers[0])', assigned value is 10
     */
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    size_t even_size = 0;

    int* even_numbers = filter_even_numbers(numbers, size, &even_size);

    if (even_numbers != NULL) {
        for (size_t i = 0; i < even_size; ++i) {
            printf("%d ", even_numbers[i]);
        }
        printf("\n");
        free(even_numbers);
    /* Possible weaknesses found:
     *  Condition 'size==0' is always false
     *  Condition 'size==0' is always false [knownConditionTrueFalse]
     */
    } else if (even_size > 0 || size == 0) {
        printf("Memory allocation failed or input was invalid.\n");
    }

    return 0;
}