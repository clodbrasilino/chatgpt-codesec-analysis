#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_even(long long number);

bool is_even(long long number)
{
    return (number % 2) == 0;
}

int main(void)
{
    long long number = 0;
    int result = 0;

    printf("Enter an integer: ");
    result = scanf("%lld", &number);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (is_even(number)) {
        printf("%lld is even: true\n", number);
    } else {
        printf("%lld is even: false\n", number);
    }

    return EXIT_SUCCESS;
}