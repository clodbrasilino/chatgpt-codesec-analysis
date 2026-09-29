#include <stdio.h>
#include <stdlib.h>

int min(int a, int b);

int min(int a, int b)
{
    if (a < b) {
        return a;
    }
    return b;
}

int main(void)
{
    int x;
    int y;
    int result;

    printf("Enter first number: ");
    if (scanf("%d", &x) != 1) {
        fprintf(stderr, "Invalid input for first number\n");
        return EXIT_FAILURE;
    }

    printf("Enter second number: ");
    if (scanf("%d", &y) != 1) {
        fprintf(stderr, "Invalid input for second number\n");
        return EXIT_FAILURE;
    }

    result = min(x, y);
    printf("The minimum of %d and %d is %d\n", x, y, result);

    return EXIT_SUCCESS;
}