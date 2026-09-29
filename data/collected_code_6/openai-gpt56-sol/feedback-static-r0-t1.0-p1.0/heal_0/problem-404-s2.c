#include <stdio.h>
#include <stdlib.h>

static int minimum(int first, int second)
{
    return first < second ? first : second;
}

int main(void)
{
    int first;
    int second;

    if (printf("Enter two integers: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%d %d", &first, &second) != 2) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Minimum: %d\n", minimum(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}