#include <stdio.h>
#include <stdlib.h>

int* square_elements(const int *list, size_t size) {
    if (list == NULL && size > 0) {
        return NULL;
    }
    
    int *squares = (int*)malloc(size * sizeof(int));
    if (squares == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < size; i++) {
        squares[i] = list[i] * list[i];
    }
    
    return squares;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    
    int *squares = square_elements(numbers, size);
    if (squares == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < size; i++) {
        printf("%d ", squares[i]);
    }
    printf("\n");
    
    free(squares);
    return EXIT_SUCCESS;
}