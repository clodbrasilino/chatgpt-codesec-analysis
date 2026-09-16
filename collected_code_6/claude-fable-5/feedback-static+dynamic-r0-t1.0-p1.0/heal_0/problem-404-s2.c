#include <stdio.h>
#include <stdlib.h>

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int main(void)
{
    int x;
    int y;

    printf("Enter first number: ");
    if (scanf("%d", &x) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter second number: ");
    if (scanf("%d", &y) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Minimum: %d\n", min(x, y));

    return EXIT_SUCCESS;
}