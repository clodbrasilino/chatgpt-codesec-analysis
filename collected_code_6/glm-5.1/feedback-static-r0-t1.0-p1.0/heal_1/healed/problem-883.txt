#include <stdio.h>
#include <stdlib.h>

int* find_divisible(const int* numbers, size_t count, int m, int n, size_t* result_count) {
    if (numbers == NULL || result_count == NULL || count == 0) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    int* result = (int*)malloc(count * sizeof(int));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    size_t res_idx = 0;
    for (size_t i = 0; i < count; i++) {
        if (m != 0 && n != 0) {
            if (numbers[i] % m == 0 && numbers[i] % n == 0) {
                result[res_idx++] = numbers[i];
            }
        }
    }

    if (res_idx == 0) {
        free(result);
        *result_count = 0;
        return NULL;
    }

    int* trimmed_result = (int*)realloc(result, res_idx * sizeof(int));
    if (trimmed_result != NULL) {
        result = trimmed_result;
    }

    *result_count = res_idx;
    return result;
}

int main(void) {
    int numbers[] = {10, 20, 33, 40, 50, 60, 73};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int m = 2;
    int n = 5;

    size_t result_count = 0;
    int* result = find_divisible(numbers, count, m, n, &result_count);

    if (result != NULL) {
        for (size_t i = 0; i < result_count; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}