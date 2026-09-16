#include <stdio.h>
#include <stdlib.h>

int sum_of_digits(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'numbers' can be declared as pointer to const [constParameterPointer]
 */
void compute_sum_of_digits(int *numbers, int size, int *result) {
    for (int i = 0; i < size; ++i) {
        result[i] = sum_of_digits(numbers[i]);
    }
}

int main() {
    int numbers[] = {123, 456, 789, 101112};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int *result = (int *)malloc(size * sizeof(int));
    
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    compute_sum_of_digits(numbers, size, result);
    
    for (int i = 0; i < size; ++i) {
        printf("%d: %d\n", numbers[i], result[i]);
    }
    
    free(result);
    return 0;
}