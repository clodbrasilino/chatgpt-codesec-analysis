#include <stdio.h>
#include <stdlib.h>

void square_elements(const int *input, int *output, size_t length) {
    for (size_t i = 0; i < length; i++) {
        output[i] = input[i] * input[i];
    }
}

int main(void) {
    const int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t count = sizeof(values) / sizeof(values[0]);
    int *squares = malloc(count * sizeof(int));
    
    if (squares == NULL) {
        return EXIT_FAILURE;
    }
    
    square_elements(values, squares, count);
    
    for (size_t i = 0; i < count; i++) {
        printf("%d ", squares[i]);
    }
    printf("\n");
    
    free(squares);
    return EXIT_SUCCESS;
}