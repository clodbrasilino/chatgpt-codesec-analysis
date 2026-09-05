#include <stdio.h>
#include <stdlib.h>

int* find_divisible_numbers(const int* numbers, size_t count, int m, int n, size_t* result_count) {
    if (numbers == NULL || result_count == NULL || m == 0 || n == 0) {
        return NULL;
    }
    
    int* result = malloc(count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    
    size_t found = 0;
    for (size_t i = 0; i < count; i++) {
        if (numbers[i] % m == 0 && numbers[i] % n == 0) {
            result[found] = numbers[i];
            found++;
        }
    }
    
    if (found == 0) {
        free(result);
        *result_count = 0;
        return NULL;
    }
    
    int* trimmed = realloc(result, found * sizeof(int));
    if (trimmed != NULL) {
        result = trimmed;
    }
    
    *result_count = found;
    return result;
}

int main(void) {
    int numbers[] = {10, 15, 30, 45, 60, 75, 90, 100, 120, 150};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int m = 3;
    int n = 5;
    size_t result_count = 0;
    
    int* divisible = find_divisible_numbers(numbers, count, m, n, &result_count);
    
    if (divisible != NULL) {
        printf("Numbers divisible by %d and %d: ", m, n);
        for (size_t i = 0; i < result_count; i++) {
            printf("%d ", divisible[i]);
        }
        printf("\n");
        free(divisible);
    } else {
        printf("No numbers found divisible by %d and %d.\n", m, n);
    }
    
    return 0;
}