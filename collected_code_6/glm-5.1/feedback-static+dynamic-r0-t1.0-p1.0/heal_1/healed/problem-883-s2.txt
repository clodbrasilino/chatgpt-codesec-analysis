#include <stdio.h>
#include <stdlib.h>

int* find_divisible(const int* numbers, int count, int m, int n, int* result_count) {
    if (numbers == NULL || result_count == NULL || count <= 0) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    if (m == 0 || n == 0) {
        *result_count = 0;
        return NULL;
    }

    int* result = (int*)malloc(count * sizeof(int));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    int idx = 0;
    for (int i = 0; i < count; i++) {
        if (numbers[i] % m == 0 && numbers[i] % n == 0) {
            result[idx++] = numbers[i];
        }
    }

    if (idx == 0) {
        free(result);
        *result_count = 0;
        return NULL;
    }

    int* final_result = (int*)realloc(result, idx * sizeof(int));
    if (final_result == NULL) {
        *result_count = idx;
        return result;
    }

    *result_count = idx;
    return final_result;
}

int main() {
    int numbers[] = {12, 24, 15, 30, 45, 60, 75, 90};
    int count = sizeof(numbers) / sizeof(numbers[0]);
    int m = 3;
    int n = 5;
    int result_count = 0;

    int* result = find_divisible(numbers, count, m, n, &result_count);

    if (result != NULL) {
        for (int i = 0; i < result_count; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}