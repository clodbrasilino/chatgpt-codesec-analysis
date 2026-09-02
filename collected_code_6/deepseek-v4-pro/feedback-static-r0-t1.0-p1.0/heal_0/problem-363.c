#include <stdlib.h>
#include <stdio.h>

void add_k_to_tuple(int *tuple, size_t size, int k) {
    for (size_t i = 0; i < size; ++i) {
        tuple[i] += k;
    }
}

int main(void) {
    size_t size;
    int k;
    
    printf("Enter tuple size: ");
    if (scanf("%zu", &size) != 1 || size == 0) {
        fprintf(stderr, "Invalid size\n");
        return EXIT_FAILURE;
    }
    
    int *tuple = (int *)malloc(size * sizeof(int));
    if (tuple == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter %zu elements: ", size);
    for (size_t i = 0; i < size; ++i) {
        if (scanf("%d", &tuple[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(tuple);
            return EXIT_FAILURE;
        }
    }
    
    printf("Enter k: ");
    if (scanf("%d", &k) != 1) {
        fprintf(stderr, "Invalid k\n");
        free(tuple);
        return EXIT_FAILURE;
    }
    
    add_k_to_tuple(tuple, size, k);
    
    printf("Result: ");
    for (size_t i = 0; i < size; ++i) {
        printf("%d ", tuple[i]);
    }
    printf("\n");
    
    free(tuple);
    return EXIT_SUCCESS;
}