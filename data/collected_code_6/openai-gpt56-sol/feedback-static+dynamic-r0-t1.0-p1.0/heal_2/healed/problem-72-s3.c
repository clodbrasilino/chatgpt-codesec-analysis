#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_difference_of_two_squares(intmax_t number)
{
    intmax_t remainder = number % 4;
    return remainder != 2 && remainder != -2;
}

int main(void)
{
    char input[128];
    char *end;
    intmax_t number;

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

    if (newline == NULL && !feof(stdin)) {
        int ch;

        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }

        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoimax(input, &end, 10);

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

    if (printf("%s\n",
               is_difference_of_two_squares(number) ? "Yes" : "No") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}