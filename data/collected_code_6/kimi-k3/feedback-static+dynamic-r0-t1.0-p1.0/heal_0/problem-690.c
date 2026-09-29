#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long multiply_consecutive(const int *list, size_t size, size_t start, size_t count, int *error) {
    long long result = 1;
    size_t i;
    
    *error = 0;
    
    if (list == NULL) {
        *error = EINVAL;
        return 0;
    }
    
    if (start >= size || count == 0 || start + count > size) {
        *error = ERANGE;
        return 0;
    }
    
    for (i = start; i < start + count; i++) {
        if (list[i] != 0 && llabs(result) > LLONG_MAX / llabs(list[i])) {
            *error = ERANGE;
            return 0;
        }
        result *= list[i];
    }
    
    return result;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int error;
    long long result;
    
    result = multiply_consecutive(numbers, size, 0, size, &error);
    if (error != 0) {
        fprintf(stderr, "Error: %s\n", error == EINVAL ? "Invalid argument" : "Range error");
        return EXIT_FAILURE;
    }
    
    printf("Product of all numbers: %lld\n", result);
    
    result = multiply_consecutive(numbers, size, 2, 4, &error);
    if (error != 0) {
        fprintf(stderr, "Error: %s\n", error == EINVAL ? "Invalid argument" : "Range error");
        return EXIT_FAILURE;
    }
    
    printf("Product of numbers from index 2 to 5: %lld\n", result);
    
    return EXIT_SUCCESS;
}