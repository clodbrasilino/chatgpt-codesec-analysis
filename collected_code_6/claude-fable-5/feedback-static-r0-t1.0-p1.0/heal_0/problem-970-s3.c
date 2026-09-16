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

    printf("Enter two integers: ");
    if (scanf("%d %d", &x, &y) != 2)
    {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Minimum: %d\n", min(x, y));

    return EXIT_SUCCESS;
}