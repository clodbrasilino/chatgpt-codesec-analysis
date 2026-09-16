#include <stdio.h>
#include <stdlib.h>

void find_divisible(const int *numbers, int length, int m, int n, int *result, int *count) {
    *count = 0;
    for (int i = 0; i < length; ++i) {
        if (numbers[i] % m == 0 && numbers[i] % n == 0) {
            result[*count] = numbers[i];
            (*count)++;
        }
    }
}

int main() {
    int numbers[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    int m = 5, n = 10;
    int *result = (int *)malloc(length * sizeof(int));
    int count;

    find_divisible(numbers, length, m, n, result, &count);

    for (int i = 0; i < count; ++i) {
        printf("%d ", result[i]);
    }

    free(result);
    return 0;
}