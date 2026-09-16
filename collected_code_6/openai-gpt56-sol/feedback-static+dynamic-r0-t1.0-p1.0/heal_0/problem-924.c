#include <stdio.h>
#include <stdlib.h>

static int maximum(int first, int second)
{
    return (first > second) ? first : second;
}

int main(void)
{
    int first = 0;
    int second = 0;

    if (printf("Enter two integers: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%d %d", &first, &second) != 2) {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum: %d\n", maximum(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}