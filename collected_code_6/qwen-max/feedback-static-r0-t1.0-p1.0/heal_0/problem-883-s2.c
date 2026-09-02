#include <stdio.h>
#include <stdlib.h>

int *find_divisible(int *numbers, int size, int m, int n, int *count) {
    *count = 0;
    for (int i = 0; i < size; ++i) {
        if (numbers[i] % m == 0 && numbers[i] % n == 0) {
            (*count)++;
        }
    }

    int *result = (int *)malloc((*count) * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    *count = 0;
    for (int i = 0; i < size; ++i) {
        if (numbers[i] % m == 0 && numbers[i] % n == 0) {
            result[*count] = numbers[i];
            (*count)++;
        }
    }

    return result;
}

int main() {
    int numbers[] = {12, 15, 24, 30, 40, 60, 75};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int m = 3;
    int n = 5;
    int count = 0;

    int *divisible = find_divisible(numbers, size, m, n, &count);

    if (divisible != NULL) {
        for (int i = 0; i < count; ++i) {
            printf("%d ", divisible[i]);
        }
        free(divisible);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}