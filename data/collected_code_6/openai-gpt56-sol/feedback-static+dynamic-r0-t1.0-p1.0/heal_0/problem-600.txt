#include <stdio.h>
#include <stdlib.h>

static int is_even(int number)
{
    return (number & 1) == 0;
}

int main(void)
{
    int number;

    if (printf("Enter an integer: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%d", &number) != 1) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (is_even(number)) {
        puts("The number is even.");
    } else {
        puts("The number is odd.");
    }

    return EXIT_SUCCESS;
}