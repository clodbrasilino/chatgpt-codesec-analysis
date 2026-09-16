#include <stdio.h>
#include <stdlib.h>

int max_of_two(int a, int b);

int max_of_two(int a, int b)
{
    return (a > b) ? a : b;
}

int main(void)
{
    int x;
    int y;
    int result;

    printf("Enter first number: ");
    if (scanf("%d", &x) != 1)
    {
        fprintf(stderr, "Invalid input for first number.\n");
        return EXIT_FAILURE;
    }

    printf("Enter second number: ");
    if (scanf("%d", &y) != 1)
    {
        fprintf(stderr, "Invalid input for second number.\n");
        return EXIT_FAILURE;
    }

    result = max_of_two(x, y);

    if (printf("Maximum: %d\n", result) < 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}