#include <stdio.h>
#include <stdlib.h>

void cube_elements(const int *input, int *output, size_t size) {
    size_t i;
    for (i = 0; i < size; ++i) {
        output[i] = input[i] * input[i] * input[i];
    }
}

int main(void) {
    int input[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(input) / sizeof(input[0]);
    int *output = (int *)malloc(size * sizeof(int));
    
    if (output == NULL) {
        return 1;
    }
    
    cube_elements(input, output, size);
    
    for (size_t i = 0; i < size; ++i) {
        printf("%d ", output[i]);
    }
    printf("\n");
    
    free(output);
    return 0;
}