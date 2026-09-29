#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_sum_of_nonzero_powers_of_two(unsigned long long number)
{
    return number != 0;
}

int main(void)
{
    char input[256];
    char *end;
    unsigned long long number;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    for (end = input; *end != '\0' && *end != '\n'; ++end) {
    }

    if (*end == '\n') {
        *end = '\0';
    } else if (!feof(stdin)) {
        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    puts(is_sum_of_nonzero_powers_of_two(number) ? "Yes" : "No");
    return EXIT_SUCCESS;
}