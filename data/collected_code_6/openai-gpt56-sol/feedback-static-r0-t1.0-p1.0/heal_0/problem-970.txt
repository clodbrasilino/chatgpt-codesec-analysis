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

    if (scanf("%d %d", &first, &second) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%d\n", minimum(first, second));

    return EXIT_SUCCESS;
}