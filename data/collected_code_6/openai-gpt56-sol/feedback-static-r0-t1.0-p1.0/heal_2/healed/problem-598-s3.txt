#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_armstrong(unsigned long long number)
{
    unsigned long long value = number;
    unsigned long long sum = 0;
    unsigned int digits = 0;

    do {
        ++digits;
        value /= 10;
    } while (value != 0);

    value = number;

    do {
        const unsigned long long digit = value % 10;
        unsigned long long power = 1;

        for (unsigned int i = 0; i < digits; ++i) {
            if (digit != 0 && power > number / digit) {
                return false;
            }
            power *= digit;
        }

        if (power > number || sum > number - power) {
            return false;
        }

        sum += power;
        value /= 10;
    } while (value != 0);

    return sum == number;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    unsigned long long number;
    size_t capacity = 0;
    ssize_t length;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    } else if (!feof(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || input[0] == '-') {
        free(input);
        return EXIT_FAILURE;
    }

    if (is_armstrong(number)) {
        printf("%llu is an Armstrong number.\n", number);
    } else {
        printf("%llu is not an Armstrong number.\n", number);
    }

    free(input);
    return EXIT_SUCCESS;
}