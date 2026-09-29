#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_odd(int number);

bool is_odd(int number)
{
    return (number & 1) != 0;
}

int main(void)
{
    int number = 0;

    printf("Enter an integer: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (is_odd(number)) {
        printf("%d is odd.\n", number);
    } else {
        printf("%d is even.\n", number);
    }

    return EXIT_SUCCESS;
}