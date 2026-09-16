#include <stdio.h>
#include <stdlib.h>

static int is_odd(long long number)
{
    return (number & 1LL) != 0;
}

int main(void)
{
    long long number;

    if (scanf("%lld", &number) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%s\n", is_odd(number) ? "Odd" : "Not odd");

    return EXIT_SUCCESS;
}