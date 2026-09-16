#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool have_opposite_signs(int x, int y)
{
    return (x ^ y) < 0;
}

int main(void)
{
    int a;
    int b;

    printf("Enter first integer: ");
    if (scanf("%d", &a) != 1) {
        fprintf(stderr, "Invalid input for first integer.\n");
        return EXIT_FAILURE;
    }

    printf("Enter second integer: ");
    if (scanf("%d", &b) != 1) {
        fprintf(stderr, "Invalid input for second integer.\n");
        return EXIT_FAILURE;
    }

    if (have_opposite_signs(a, b)) {
        printf("%d and %d have opposite signs.\n", a, b);
    } else {
        printf("%d and %d do not have opposite signs.\n", a, b);
    }

    return EXIT_SUCCESS;
}