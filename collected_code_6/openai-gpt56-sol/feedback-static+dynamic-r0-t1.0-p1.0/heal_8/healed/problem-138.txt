#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static bool is_power_of_two(unsigned long long value)
{
    return value != 0ULL && (value & (value - 1ULL)) == 0ULL;
}

static bool is_sum_of_two_nonzero_powers_of_two(unsigned long long number)
{
    unsigned int set_bits = 0;

    while (number != 0ULL) {
        number &= number - 1ULL;
        ++set_bits;
    }

    return set_bits == 2U;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *start;
    char *end;
    unsigned long long number;
    bool result;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    while (length > 0 &&
           (input[length - 1] == '\n' || input[length - 1] == '\r')) {
        input[--length] = '\0';
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    result = !is_power_of_two(number) &&
             is_sum_of_two_nonzero_powers_of_two(number);

    puts(result ? "True" : "False");

    free(input);
    return EXIT_SUCCESS;
}