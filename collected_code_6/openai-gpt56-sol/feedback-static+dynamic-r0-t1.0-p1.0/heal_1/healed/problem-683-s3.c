#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_sum_of_two_squares(unsigned long long value)
{
    unsigned long long left = 0;
    unsigned long long right = value < ULLONG_MAX ? value + 1 : value;

    while (left < right) {
        unsigned long long middle = left + (right - left) / 2;

        if (middle != 0 && middle > value / middle) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }

    unsigned long long a = 0;
    unsigned long long b = left - 1;
    unsigned long long a_squared = 0;
    unsigned long long b_squared = b * b;

    while (a <= b) {
        unsigned long long remainder = value - b_squared;

        if (a_squared == remainder) {
            return true;
        }

        if (a_squared < remainder) {
            ++a;
            a_squared = a * a;
        } else {
            b_squared -= 2 * b - 1;
            --b;
        }
    }

    return false;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    unsigned long long value;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoull(input, &end, 10);

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

    puts(is_sum_of_two_squares(value) ? "Yes" : "No");

    free(input);
    return EXIT_SUCCESS;
}