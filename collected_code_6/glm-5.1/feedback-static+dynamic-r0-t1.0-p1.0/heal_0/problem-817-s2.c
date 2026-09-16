#include <stdio.h>
#include <stdlib.h>

int* find_divisible(const int* numbers, size_t count, int m, int n, size_t* result_count) {
    if (numbers == NULL || result_count == NULL || count == 0) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    if (m == 0 || n == 0) {
        *result_count = 0;
        return NULL;
    }

    int* temp = (int*)malloc(count * sizeof(int));
    if (temp == NULL) {
        *result_count = 0;
        return NULL;
    }

    size_t res_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (numbers[i] % m == 0 || numbers[i] % n == 0) {
            temp[res_count++] = numbers[i];
        }
    }

    int* result = (int*)realloc(temp, res_count * sizeof(int));
    if (result == NULL) {
        if (res_count > 0) {
            result = temp;
        } else {
            free(temp);
        }
    }

    *result_count = res_count;
    return result;
}

int main(void) {
    int numbers[] = {10, 15, 22, 30, 45, 50, 7, 13};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int m = 5;
    int n = 7;

    size_t result_count = 0;
    int* result = find_divisible(numbers, count, m, n, &result_count);

    if (result != NULL) {
        for (size_t i = 0; i < result_count; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("No numbers found or invalid input.\n");
    }

    return 0;
}