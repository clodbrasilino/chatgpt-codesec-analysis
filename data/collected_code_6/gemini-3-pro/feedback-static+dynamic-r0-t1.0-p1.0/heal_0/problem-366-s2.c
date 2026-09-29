#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_largest_adjacent_product(const int *array, size_t size) {
    if (array == NULL || size < 2) {
        return INT_MIN;
    }

    int max_product = INT_MIN;
    
    for (size_t i = 0; i < size - 1; i++) {
        long long current_product = (long long)array[i] * array[i + 1];
        if (current_product > max_product) {
            max_product = (int)current_product;
        }
    }

    return max_product;
}

int main(void) {
    int array[] = {3, 6, -2, -5, 7, 3};
    size_t size = sizeof(array) / sizeof(array[0]);

    int result = find_largest_adjacent_product(array, size);
    
    if (result != INT_MIN) {
        printf("%d\n", result);
    } else {
        printf("Error: Invalid array or size.\n");
    }

    return EXIT_SUCCESS;
}