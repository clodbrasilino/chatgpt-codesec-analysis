#include <stdio.h>
#include <stdlib.h>

int* find_divisible(const int* numbers, size_t count, int m, int n, size_t* result_count) {
    if (numbers == NULL || result_count == NULL || (m == 0 && n == 0)) {
        return NULL;
    }

    int* temp = (int*)malloc(count * sizeof(int));
    if (temp == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < count; i++) {
        if ((m != 0 && numbers[i] % m == 0) || (n != 0 && numbers[i] % n == 0)) {
            temp[j++] = numbers[i];
        }
    }

    if (j == 0) {
        free(temp);
        *result_count = 0;
        return NULL;
    }

    int* result = (int*)malloc(j * sizeof(int));
    if (result == NULL) {
        free(temp);
        *result_count = 0;
        return NULL;
    }

    for (size_t i = 0; i < j; i++) {
        result[i] = temp[i];
    }

    free(temp);
    *result_count = j;
    return result;
}

int main(void) {
    int nums[] = {10, 15, 20, 25, 30, 35, 40};
    size_t count = sizeof(nums) / sizeof(nums[0]);
    int m = 5;
    int n = 7;
    size_t result_count = 0;

    int* result = find_divisible(nums, count, m, n, &result_count);

    if (result != NULL) {
        for (size_t i = 0; i < result_count; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("No matching numbers found or invalid input provided.\n");
    }

    return 0;
}