#include <stdio.h>
#include <stdlib.h>

int* find_divisible_by_m_and_n(const int* numbers, size_t size, int m, int n, size_t* result_size) {
    if (numbers == NULL || result_size == NULL || m == 0 || n == 0) {
        *result_size = 0;
        return NULL;
    }

    int* result = (int*)malloc(size * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (numbers[i] % m == 0 && numbers[i] % n == 0) {
            result[count++] = numbers[i];
        }
    }

    if (count == 0) {
        free(result);
        *result_size = 0;
        return NULL;
    }

    int* resized = (int*)realloc(result, count * sizeof(int));
    if (resized == NULL && count > 0) {
        free(result);
        *result_size = 0;
        return NULL;
    }

    *result_size = count;
    return resized;
}

int main(void) {
    int numbers[] = {12, 24, 36, 48, 60, 15, 30, 45, 90, 100, 120, 180};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int m = 3;
    int n = 4;

    size_t result_size = 0;
    int* result = find_divisible_by_m_and_n(numbers, size, m, n, &result_size);

    if (result != NULL) {
        printf("Numbers divisible by %d and %d: ", m, n);
        for (size_t i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("No numbers found divisible by both %d and %d\n", m, n);
    }

    return 0;
}