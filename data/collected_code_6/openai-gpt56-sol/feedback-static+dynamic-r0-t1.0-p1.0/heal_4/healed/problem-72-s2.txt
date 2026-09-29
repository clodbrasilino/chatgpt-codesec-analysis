#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_difference_of_two_squares(int64_t number)
{
    int64_t remainder = number % 4;
    return remainder != 2 && remainder != -2;
}

int main(void)
{
    char input[128];
    char *end;
    intmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    char *newline = NULL;

    for (size_t i = 0; i < sizeof input; ++i) {
        if (input[i] == '\n') {
            newline = &input[i];
            break;
        }

        if (input[i] == '\0') {
            break;
        }
    }

    if (newline != NULL) {
        *newline = '\0';
    } else {
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    end = NULL;
    value = strtoimax(input, &end, 10);

    if (end == input || errno == ERANGE ||
        value < INT64_MIN || value > INT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_difference_of_two_squares((int64_t)value) ? "Yes" : "No");
    return EXIT_SUCCESS;
}