#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

int calculate_differences(const int *numbers, size_t count, int *differences, size_t diff_capacity)
{
    size_t i;
    size_t required_size;

    if (numbers == NULL || differences == NULL) {
        return -1;
    }

    if (count < 2) {
        return 0;
    }

    required_size = count - 1;
    if (diff_capacity < required_size) {
        return -1;
    }

    for (i = 0; i < required_size; i++) {
        long temp_diff = (long)numbers[i + 1] - (long)numbers[i];
        
        if (temp_diff > INT_MAX || temp_diff < INT_MIN) {
            return -1;
        }
        
        differences[i] = (int)temp_diff;
    }

    return (int)required_size;
}

int main(void)
{
    int numbers[] = {10, 25, 30, 45, 50, 75};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    size_t diff_count = count - 1;
    int *differences = NULL;
    int result;
    size_t i;

    if (diff_count > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Size calculation overflow\n");
        return EXIT_FAILURE;
    }
    
    differences = malloc(diff_count * sizeof(int));
    if (differences == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    result = calculate_differences(numbers, count, differences, diff_count);
    
    if (result < 0) {
        fprintf(stderr, "Error calculating differences\n");
        free(differences);
        return EXIT_FAILURE;
    }

    printf("Original list: ");
    for (i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    printf("Differences: ");
    for (i = 0; i < (size_t)result; i++) {
        printf("%d ", differences[i]);
    }
    printf("\n");

    free(differences);
    return EXIT_SUCCESS;
}