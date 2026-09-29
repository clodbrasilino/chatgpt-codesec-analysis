#include <stdio.h>
#include <stdlib.h>

void find_cubes(const int *input, int *output, size_t length) {
    for (size_t i = 0; i < length; i++) {
        output[i] = input[i] * input[i] * input[i];
    }
}

int main(void) {
    int input[] = {1, 2, 3, 4, 5};
    size_t length = sizeof(input) / sizeof(input[0]);
    int *output = malloc(length * sizeof(int));
    
    if (output == NULL) {
        return 1;
    }
    
    find_cubes(input, output, length);
    
    for (size_t i = 0; i < length; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");
    
    free(output);
    return 0;
}