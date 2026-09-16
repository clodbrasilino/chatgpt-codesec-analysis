#include <stdio.h>
#include <stdlib.h>

static int min_int(int first, int second)
{
    return (first < second) ? first : second;
}

int main(void)
{
    int first;
    int second;

    if (scanf("%d %d", &first, &second) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%d\n", min_int(first, second));
    return EXIT_SUCCESS;
}