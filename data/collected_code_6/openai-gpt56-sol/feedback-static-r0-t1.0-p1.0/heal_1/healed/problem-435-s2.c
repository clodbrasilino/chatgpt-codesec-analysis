#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int last_digit(long long number)
{
    int digit = (int)(number % 10);
    return digit < 0 ? -digit : digit;
}

int main(void)
{
    char input[128];
    char *end;
    long long number;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (input[0] != '\0' && input[sizeof input - 2] != '\n') {
        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    end = NULL;
    number = strtoll(input, &end, 10);

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

    if (printf("%d\n", last_digit(number)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}