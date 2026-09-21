#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_perfect_square(unsigned long long number)
{
    unsigned long long left = 0;
    unsigned long long right = number;

    while (left <= right) {
        unsigned long long middle = left + (right - left) / 2;

        if (middle != 0 && middle > number / middle) {
            right = middle - 1;
        } else {
            unsigned long long square = middle * middle;

            if (square == number) {
                return true;
            }

            left = middle + 1;
        }
    }

    return false;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *start;
    char *end;
    unsigned long long number;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    start = input;
    while (*start == ' ' || *start == '\t' || *start == '\n' ||
           *start == '\r' || *start == '\f' || *start == '\v') {
        ++start;
    }

    if (*start == '-') {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    printf("%llu is%s a perfect square.\n",
           number, is_perfect_square(number) ? "" : " not");

    free(input);
    return EXIT_SUCCESS;
}