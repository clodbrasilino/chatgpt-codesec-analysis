#include <stdio.h>
#include <stdlib.h>

int min(int a, int b);

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int main(void)
{
    int x;
    int y;
    int result;

    printf("Enter first number: ");
    if (scanf("%d", &x) != 1) {
        fprintf(stderr, "Error: invalid input for first number\n");
        return EXIT_FAILURE;
    }

    printf("Enter second number: ");
    if (scanf("%d", &y) != 1) {
        fprintf(stderr, "Error: invalid input for second number\n");
        return EXIT_FAILURE;
    }

    result = min(x, y);
    printf("Minimum: %d\n", result);

    return EXIT_SUCCESS;
}