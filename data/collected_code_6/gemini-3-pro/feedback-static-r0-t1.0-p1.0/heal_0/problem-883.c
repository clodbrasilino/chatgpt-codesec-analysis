#include <stdio.h>
#include <stdlib.h>

void findDivisibleNumbers(const int* numbers, size_t length, int m, int n, int** result, size_t* result_length) {
    if (numbers == NULL || result == NULL || result_length == NULL) {
        return;
    }

    if (m == 0 || n == 0) {
        *result = NULL;
        *result_length = 0;
        return;
    }

    size_t count = 0;
    for (size_t i = 0; i < length; ++i) {
        if (numbers[i] % m == 0 && numbers[i] % n == 0) {
            count++;
        }
    }

    if (count == 0) {
        *result = NULL;
        *result_length = 0;
        return;
    }

    *result = (int*)malloc(count * sizeof(int));
    if (*result == NULL) {
        *result_length = 0;
        return;
    }

    size_t index = 0;
    for (size_t i = 0; i < length; ++i) {
        if (numbers[i] % m == 0 && numbers[i] % n == 0) {
            (*result)[index++] = numbers[i];
        }
    }

    *result_length = count;
}

int main(void) {
    int numbers[] = {12, 15, 24, 30, 36, 45, 60};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    int m = 3;
    int n = 4;
    int* result = NULL;
    size_t result_length = 0;

    findDivisibleNumbers(numbers, length, m, n, &result, &result_length);

    if (result != NULL && result_length > 0) {
        for (size_t i = 0; i < result_length; ++i) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
        result = NULL;
    }

    return 0;
}