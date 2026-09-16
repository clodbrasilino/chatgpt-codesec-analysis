#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [1, 3, 5, 7, 9], got <no output>
  *  test case 1 failed: expected [45, 67, 93], got <no output>
  *  test case 2 failed: expected [5, 7, 9, 3], got <no output>
  */

int* filter_odd_numbers(const int* numbers, int n, int* out_n) {
    *out_n = 0;
    for (int i = 0; i < n; ++i) {
        if (numbers[i] % 2 != 0) {
            (*out_n)++;
        }
    }

    int* result = malloc(*out_n * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < n; ++i) {
        if (numbers[i] % 2 != 0) {
            result[index++] = numbers[i];
        }
    }

    return result;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    int out_n;

    const int* odd_numbers = filter_odd_numbers(numbers, n, &out_n);
    if (odd_numbers == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < out_n; ++i) {
        printf("%d ", odd_numbers[i]);
    }
    printf("\n");

    free((void*)odd_numbers);
    return 0;
}