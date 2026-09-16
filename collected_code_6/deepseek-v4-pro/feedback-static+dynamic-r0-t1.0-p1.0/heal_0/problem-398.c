#include <stdio.h>
#include <stdlib.h>

int sum_of_digits(int n) {
    int sum = 0;
    n = abs(n);
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum == 0 ? 0 : sum;
}

int* sum_digits_list(const int* numbers, size_t count, size_t* out_count) {
    if (out_count == NULL) {
        return NULL;
    }
    if (numbers == NULL && count > 0) {
        *out_count = 0;
        return NULL;
    }
    int* results = (int*)malloc(count * sizeof(int));
    if (results == NULL && count > 0) {
        *out_count = 0;
        return NULL;
    }
    for (size_t i = 0; i < count; ++i) {
        results[i] = sum_of_digits(numbers[i]);
    }
    *out_count = count;
    return results;
}

int main(void) {
    int numbers[] = {123, -456, 7890, 0, 1001};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    size_t result_count = 0;
    int* sums = sum_digits_list(numbers, count, &result_count);
    if (sums == NULL && result_count != 0) {
        return 1;
    }
    for (size_t i = 0; i < result_count; ++i) {
        printf("%d ", sums[i]);
    }
    printf("\n");
    if (sums != NULL) {
        free(sums);
        sums = NULL;
    }
    return 0;
}