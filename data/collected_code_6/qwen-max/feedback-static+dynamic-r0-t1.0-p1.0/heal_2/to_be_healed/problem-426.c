#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [1, 3, 5, 7, 9], got <no output>
  *  test case 1 failed: expected [45, 67, 93], got <no output>
  *  test case 2 failed: expected [5, 7, 9, 3], got <no output>
  */

int* filter_odd_numbers(const int* numbers, size_t count, size_t* return_count) {
    *return_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (numbers[i] % 2 != 0) {
            (*return_count)++;
        }
    }

    int* result = malloc(*return_count * sizeof(int));
    if (!result) {
        return NULL;
    }

    *return_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (numbers[i] % 2 != 0) {
            result[*return_count] = numbers[i];
            (*return_count)++;
        }
    }

    return result;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    size_t return_count;

    int* odd_numbers = filter_odd_numbers(numbers, count, &return_count);

    if (odd_numbers) {
        for (size_t i = 0; i < return_count; i++) {
            printf("%d ", odd_numbers[i]);
        }
        free(odd_numbers);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}