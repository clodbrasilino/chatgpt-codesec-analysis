#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool have_opposite_signs(int a, int b)
{
    return (a ^ b) < 0;
}

int main(void)
{
    int x;
    int y;

    printf("Enter first integer: ");
    if (scanf("%d", &x) != 1) {
        fprintf(stderr, "Invalid input for first integer.\n");
        return EXIT_FAILURE;
    }

    printf("Enter second integer: ");
    if (scanf("%d", &y) != 1) {
        fprintf(stderr, "Invalid input for second integer.\n");
        return EXIT_FAILURE;
    }

    if (have_opposite_signs(x, y)) {
        printf("%d and %d have opposite signs.\n", x, y);
    } else {
        printf("%d and %d do not have opposite signs.\n", x, y);
    }

    return EXIT_SUCCESS;
}