#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool reverse_number(long long number, long long *reversed)
{
    long long result = 0;
    long long value = number;

    if (reversed == NULL || number < 0) {
        return false;
    }

    do {
        const int digit = (int)(value % 10);

        if (result > (LLONG_MAX - digit) / 10) {
            return false;
        }

        result = result * 10 + digit;
        value /= 10;
    } while (value != 0);

    *reversed = result;
    return true;
}

static bool is_one_less_than_twice_reverse(long long number)
{
    long long reversed = 0;

    if (!reverse_number(number, &reversed)) {
        return false;
    }

    return reversed <= LLONG_MAX / 2 && number == (2 * reversed) - 1;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    long long number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoll(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return EXIT_FAILURE;
    }

    printf("%s\n",
           is_one_less_than_twice_reverse(number) ? "true" : "false");

    return EXIT_SUCCESS;
}