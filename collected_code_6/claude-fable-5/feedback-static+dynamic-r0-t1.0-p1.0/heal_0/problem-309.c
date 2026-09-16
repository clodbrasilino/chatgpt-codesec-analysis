#include <stdio.h>
#include <stdlib.h>

int max_of_two(int a, int b);

int max_of_two(int a, int b)
{
    return (a > b) ? a : b;
}

int main(void)
{
    int a;
    int b;
    int result;

    printf("Enter first number: ");
    if (scanf("%d", &a) != 1) {
        fprintf(stderr, "Invalid input for first number\n");
        return EXIT_FAILURE;
    }

    printf("Enter second number: ");
    if (scanf("%d", &b) != 1) {
        fprintf(stderr, "Invalid input for second number\n");
        return EXIT_FAILURE;
    }

    result = max_of_two(a, b);
    printf("Maximum: %d\n", result);

    return EXIT_SUCCESS;
}