#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void print_positive_numbers(const int *list, size_t size) {
    size_t i;
    
    if (list == NULL) {
        fprintf(stderr, "Error: NULL pointer provided\n");
        return;
    }
    
    for (i = 0; i < size; i++) {
        if (list[i] > 0) {
            printf("%d\n", list[i]);
        }
    }
}

int main(void) {
    int *numbers = NULL;
    size_t count = 0;
    size_t i;
    int input;
    
    printf("Enter the number of elements: ");
    
    if (scanf("%d", &input) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (input <= 0) {
        fprintf(stderr, "Error: Invalid count\n");
        return EXIT_FAILURE;
    }
    
    count = (size_t)input;
    
    numbers = (int *)malloc(count * sizeof(int));
    
    if (numbers == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter %d integers:\n", input);
    
    for (i = 0; i < count; i++) {
        if (scanf("%d", &numbers[i]) != 1) {
            fprintf(stderr, "Error: Invalid input\n");
            free(numbers);
            numbers = NULL;
            return EXIT_FAILURE;
        }
    }
    
    printf("Positive numbers:\n");
    print_positive_numbers(numbers, count);
    
    free(numbers);
    numbers = NULL;
    
    return EXIT_SUCCESS;
}