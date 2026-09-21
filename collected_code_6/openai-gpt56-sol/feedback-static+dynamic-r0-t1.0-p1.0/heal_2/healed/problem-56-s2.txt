#include <errno.h>
#include <limits.h>
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
        int digit = (int)(value % 10);

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
    long long reversed;

    if (!reverse_number(number, &reversed)) {
        return false;
    }

    return reversed <= LLONG_MAX / 2 &&
           number == (2 * reversed) - 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    long long number;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    }

    errno = 0;
    number = strtoll(input, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' ||
           *end == '\r' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    printf("%s\n",
           is_one_less_than_twice_reverse(number) ? "true" : "false");

    free(input);
    return EXIT_SUCCESS;
}