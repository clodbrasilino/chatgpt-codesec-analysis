#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool have_equal_digit_products(uintmax_t number)
{
    uintmax_t even_product = 1;
    uintmax_t odd_product = 1;
    size_t position = 1;

    do {
        const uintmax_t digit = number % 10;

        if (position % 2 == 0) {
            even_product *= digit;
        } else {
            odd_product *= digit;
        }

        number /= 10;
        ++position;
    } while (number != 0);

    return even_product == odd_product;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    uintmax_t number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    puts(have_equal_digit_products(number) ? "Equal" : "Not equal");

    return EXIT_SUCCESS;
}