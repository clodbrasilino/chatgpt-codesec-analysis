#include <stdio.h>
#include <stdlib.h>

void cube_elements(const int *input, long long *output, size_t size)
{
    size_t i;

    if (input == NULL || output == NULL) {
        return;
    }

    for (i = 0; i < size; i++) {
        output[i] = (long long)input[i] * input[i] * input[i];
    }
}

int main(void)
{
    int input[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(input) / sizeof(input[0]);
    long long *output;
    size_t i;

    output = (long long *)malloc(size * sizeof(long long));
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    cube_elements(input, output, size);

    printf("Original elements: ");
    for (i = 0; i < size; i++) {
        printf("%d ", input[i]);
    }
    printf("\n");

    printf("Cubed elements: ");
    for (i = 0; i < size; i++) {
        printf("%lld ", output[i]);
    }
    printf("\n");

    free(output);
    output = NULL;

    return EXIT_SUCCESS;
}