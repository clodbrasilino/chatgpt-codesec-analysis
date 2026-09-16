#include <stdio.h>
#include <stdlib.h>

static int maximum(int first, int second)
{
    return (first > second) ? first : second;
}

int main(void)
{
    int first;
    int second;

    if (scanf("%d %d", &first, &second) != 2) {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("%d\n", maximum(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}