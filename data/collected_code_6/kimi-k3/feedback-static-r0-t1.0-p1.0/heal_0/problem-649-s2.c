#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int calculate_range_sum(const int *arr, size_t size, size_t start, size_t end, int *result)
{
    if (arr == NULL || result == NULL) {
        return -1;
    }
    
    if (start >= size || end >= size || start > end) {
        return -1;
    }
    
    int sum = 0;
    for (size_t i = start; i <= end; i++) {
        if (arr[i] > 0 && sum > INT_MAX - arr[i]) {
            return -1;
        }
        if (arr[i] < 0 && sum < INT_MIN - arr[i]) {
            return -1;
        }
        sum += arr[i];
    }
    
    *result = sum;
    return 0;
}

int main(void)
{
    int *numbers = NULL;
    size_t count = 0;
    size_t start = 0;
    size_t end = 0;
    int sum = 0;
    int status = 0;
    
    printf("Enter number of elements: ");
    if (scanf("%zu", &count) != 1 || count == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter %zu integers:\n", count);
    for (size_t i = 0; i < count; i++) {
        if (scanf("%d", &numbers[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(numbers);
            return EXIT_FAILURE;
        }
    }
    
    printf("Enter start and end indices (0-based): ");
    if (scanf("%zu %zu", &start, &end) != 2) {
        fprintf(stderr, "Invalid indices\n");
        free(numbers);
        return EXIT_FAILURE;
    }
    
    status = calculate_range_sum(numbers, count, start, end, &sum);
    if (status != 0) {
        fprintf(stderr, "Error: Invalid range or integer overflow\n");
        free(numbers);
        return EXIT_FAILURE;
    }
    
    printf("Sum of elements from index %zu to %zu: %d\n", start, end, sum);
    
    free(numbers);
    return EXIT_SUCCESS;
}