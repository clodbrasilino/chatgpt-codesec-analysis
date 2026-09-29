#include <stdio.h>
#include <stdlib.h>

static int median_of_three(int a, int b, int c)
{
    if ((a <= b && b <= c) || (c <= b && b <= a)) {
        return b;
    }

    if ((b <= a && a <= c) || (c <= a && a <= b)) {
        return a;
    }

    return c;
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

    printf("%d\n", median_of_three(a, b, c));

    return EXIT_SUCCESS;
}