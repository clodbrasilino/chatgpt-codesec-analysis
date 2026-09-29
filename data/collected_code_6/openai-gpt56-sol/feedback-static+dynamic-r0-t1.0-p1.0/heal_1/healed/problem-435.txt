#include <errno.h>
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

    if (input[0] == '\0') {
        return EXIT_FAILURE;
    }

    if (input[sizeof input - 2] != '\n') {
        for (ch = getchar(); ch != '\n' && ch != EOF; ch++) {
        }

        if (ch != EOF || input[sizeof input - 2] != '\0') {
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    number = strtoll(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        end++;
    }

    if (*end != '\n' && *end != '\0') {
        return EXIT_FAILURE;
    }

    printf("%d\n", last_digit(number));
    return EXIT_SUCCESS;
}