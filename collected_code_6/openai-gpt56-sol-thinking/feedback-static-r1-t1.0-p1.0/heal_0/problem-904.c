#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_even(int number)
{
    return number % 2 == 0;
}

int main(void)
{
    int number;

    if (scanf("%d", &number) != 1) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", is_even(number) ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}