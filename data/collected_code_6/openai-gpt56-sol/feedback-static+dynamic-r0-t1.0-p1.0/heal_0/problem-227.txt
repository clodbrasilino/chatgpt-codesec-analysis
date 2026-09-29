#include <stdio.h>
#include <stdlib.h>

static int minimum_of_three(int a, int b, int c)
{
    int minimum = a;

    if (b < minimum) {
        minimum = b;
    }

    if (c < minimum) {
        minimum = c;
    }

    return minimum;
}

int main(void)
{
    int a;
    int b;
    int c;

    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%d\n", minimum_of_three(a, b, c));

    return EXIT_SUCCESS;
}