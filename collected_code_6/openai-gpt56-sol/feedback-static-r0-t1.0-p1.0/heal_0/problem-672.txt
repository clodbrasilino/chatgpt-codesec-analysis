#include <stdio.h>
#include <stdlib.h>

static int maximum_of_three(int a, int b, int c)
{
    int maximum = a;

    if (b > maximum) {
        maximum = b;
    }

    if (c > maximum) {
        maximum = c;
    }

    return maximum;
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

    printf("%d\n", maximum_of_three(a, b, c));

    return EXIT_SUCCESS;
}