#include <stdio.h>
#include <stdlib.h>

static int products_are_equal(unsigned long long number)
{
    unsigned long long even_product = 1U;
    unsigned long long odd_product = 1U;
    unsigned int position = 1U;

    do {
        unsigned int digit = (unsigned int)(number % 10U);

        if ((position % 2U) == 0U) {
            even_product *= digit;
        } else {
            odd_product *= digit;
        }

        number /= 10U;
        ++position;
    } while (number != 0U);

    return even_product == odd_product;
}

int main(void)
{
    unsigned long long number;
    char trailing;

    if (scanf("%llu", &number) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (scanf(" %c", &trailing) == 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(products_are_equal(number) ? "Equal" : "Not equal");
    return EXIT_SUCCESS;
}