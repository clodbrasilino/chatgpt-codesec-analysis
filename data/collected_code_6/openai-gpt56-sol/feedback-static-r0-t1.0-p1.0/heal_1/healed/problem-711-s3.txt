#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool products_are_equal(uintmax_t number)
{
    uintmax_t even_product = 1;
    uintmax_t odd_product = 1;
    size_t position = 1;

    do {
        const uintmax_t digit = number % 10U;

        if (position % 2U == 0U) {
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
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    uintmax_t number;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    puts(products_are_equal(number) ? "Equal" : "Not equal");

    free(input);
    return EXIT_SUCCESS;
}