#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_even(int number)
{
    return (number & 1) == 0;
}

int main(void)
{
    int number;

    printf("Enter an integer: ");

    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (is_even(number)) {
        printf("%d is even.\n", number);
    } else {
        printf("%d is odd.\n", number);
    }

    return EXIT_SUCCESS;
}