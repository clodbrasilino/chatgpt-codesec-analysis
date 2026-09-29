#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_armstrong(unsigned long long number)
{
    unsigned long long temp = number;
    unsigned long long sum = 0;
    unsigned int digits = 0;

    do {
        ++digits;
        temp /= 10;
    } while (temp != 0);

    temp = number;

    do {
        unsigned long long digit = temp % 10;
        unsigned long long power = 1;

        for (unsigned int i = 0; i < digits; ++i) {
            if (digit != 0 && power > ULLONG_MAX / digit) {
                return false;
            }
            power *= digit;
        }

        if (sum > ULLONG_MAX - power) {
            return false;
        }

        sum += power;
        temp /= 10;
    } while (temp != 0);

    return sum == number;
}

int main(void)
{
    char input[128];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    char *newline = NULL;

    for (char *p = input; *p != '\0'; ++p) {
        if (*p == '\n') {
            newline = p;
            break;
        }
    }

    if (newline != NULL) {
        *newline = '\0';
    } else {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ch == EOF && ferror(stdin)) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    char *start = input;

    while (*start == ' ' || *start == '\t' || *start == '\r' ||
           *start == '\f' || *start == '\v') {
        ++start;
    }

    if (*start == '-') {
        puts("Not an Armstrong number");
        return EXIT_SUCCESS;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    puts(is_armstrong(number)
             ? "Armstrong number"
             : "Not an Armstrong number");

    return EXIT_SUCCESS;
}