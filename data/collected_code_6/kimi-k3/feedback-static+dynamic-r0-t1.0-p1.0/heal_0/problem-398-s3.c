#include <stdio.h>
#include <stdlib.h>

int sum_of_digits(int number) {
    int sum = 0;
    int n = abs(number);
    
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    
    return sum;
}

int main(void) {
    int size;
    
    if (printf("Enter the number of elements: ") < 0) {
        return EXIT_FAILURE;
    }
    
    if (scanf("%d", &size) != 1 || size <= 0) {
        fprintf(stderr, "Invalid input for size\n");
        return EXIT_FAILURE;
    }
    
    int *numbers = malloc((size_t)size * sizeof(int));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    int *sums = malloc((size_t)size * sizeof(int));
    if (sums == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(numbers);
        return EXIT_FAILURE;
    }
    
    printf("Enter %d integers: ", size);
    for (int i = 0; i < size; i++) {
        if (scanf("%d", &numbers[i]) != 1) {
            fprintf(stderr, "Invalid input for number %d\n", i + 1);
            free(numbers);
            free(sums);
            return EXIT_FAILURE;
        }
    }
    
    for (int i = 0; i < size; i++) {
        sums[i] = sum_of_digits(numbers[i]);
    }
    
    printf("Sum of digits for each number:\n");
    for (int i = 0; i < size; i++) {
        if (printf("Number %d: %d\n", numbers[i], sums[i]) < 0) {
            fprintf(stderr, "Output error\n");
            free(numbers);
            free(sums);
            return EXIT_FAILURE;
        }
    }
    
    free(numbers);
    free(sums);
    
    return EXIT_SUCCESS;
}