#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isProductEven(int* numbers, size_t count) {
    if (numbers == NULL || count == 0) {
        return false; 
    }

    for (size_t i = 0; i < count; i++) {
        if (numbers[i] % 2 == 0) {
            return true;
        }
    }

    return false;
}

int main(void) {
    size_t count;
    
    if (scanf("%zu", &count) != 1) {
        return EXIT_FAILURE;
    }

    if (count == 0) {
        return EXIT_SUCCESS;
    }

    int* numbers = (int*)malloc(count * sizeof(int));
    if (numbers == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        if (scanf("%d", &numbers[i]) != 1) {
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    bool result = isProductEven(numbers, count);
    
    if (result) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }

    free(numbers);
    return EXIT_SUCCESS;
}