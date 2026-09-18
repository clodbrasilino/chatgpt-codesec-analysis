#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected [5, 7, 9, 3], got <no output>
  *  test case 1 failed: expected [45, 67, 93], got <no output>
  *  test case 0 failed: expected [1, 3, 5, 7, 9], got <no output>
  */

int* filter_odd_numbers(const int* input, size_t input_size, size_t* output_size) {
    if (input == NULL || output_size == NULL) {
        if (output_size != NULL) {
            *output_size = 0;
        }
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < input_size; i++) {
        if (input[i] % 2 != 0) {
            count++;
        }
    }

    *output_size = count;

    if (count == 0) {
        return NULL;
    }

    int* output = (int*)malloc(count * sizeof(int));
    if (output == NULL) {
        *output_size = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < input_size; i++) {
        if (input[i] % 2 != 0) {
            output[index++] = input[i];
        }
    }

    return output;
}

int main(void) {
    int input1[] = {1, 3, 5, 7, 9};
    size_t input_size1 = sizeof(input1) / sizeof(input1[0]);
    size_t output_size1 = 0;
    int* odd_numbers1 = filter_odd_numbers(input1, input_size1, &output_size1);
    if (odd_numbers1 != NULL) {
        printf("[");
        for (size_t i = 0; i < output_size1; i++) {
            if (i > 0) printf(", ");
            printf("%d", odd_numbers1[i]);
        }
        printf("]\n");
        free(odd_numbers1);
    } else {
        printf("[]\n");
    }

    int input2[] = {45, 67, 93};
    size_t input_size2 = sizeof(input2) / sizeof(input2[0]);
    size_t output_size2 = 0;
    int* odd_numbers2 = filter_odd_numbers(input2, input_size2, &output_size2);
    if (odd_numbers2 != NULL) {
        printf("[");
        for (size_t i = 0; i < output_size2; i++) {
            if (i > 0) printf(", ");
            printf("%d", odd_numbers2[i]);
        }
        printf("]\n");
        free(odd_numbers2);
    } else {
        printf("[]\n");
    }

    int input3[] = {5, 7, 9, 3};
    size_t input_size3 = sizeof(input3) / sizeof(input3[0]);
    size_t output_size3 = 0;
    int* odd_numbers3 = filter_odd_numbers(input3, input_size3, &output_size3);
    if (odd_numbers3 != NULL) {
        printf("[");
        for (size_t i = 0; i < output_size3; i++) {
            if (i > 0) printf(", ");
            printf("%d", odd_numbers3[i]);
        }
        printf("]\n");
        free(odd_numbers3);
    } else {
        printf("[]\n");
    }

    return 0;
}