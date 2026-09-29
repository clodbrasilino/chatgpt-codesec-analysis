#include <stdio.h>
#include <stdlib.h>

static int count_equal_numbers(int a, int b, int c)
{
    if (a == b && b == c) {
        return 3;
    }

    if (a == b || a == c || b == c) {
        return 2;
    }

    return 0;
}

int main(void)
{
    int a;
    int b;
    int c;

    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", count_equal_numbers(a, b, c));
    return EXIT_SUCCESS;
}