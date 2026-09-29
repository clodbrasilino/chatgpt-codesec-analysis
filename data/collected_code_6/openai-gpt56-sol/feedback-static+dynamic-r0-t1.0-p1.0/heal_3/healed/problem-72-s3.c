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

static bool read_line(char *buffer, size_t size)
{
    if (size < 2 || fgets(buffer, size, stdin) == NULL) {
        return false;
    }

    for (char *p = buffer; *p != '\0'; ++p) {
        if (*p == '\n') {
            *p = '\0';
            return true;
        }
    }

    if (feof(stdin)) {
        return true;
    }

    int ch;
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return false;
}

int main(void)
{
    char input[128];
    char *end = NULL;

    if (!read_line(input, sizeof input)) {
        return EXIT_FAILURE;
    }

    errno = 0;
    intmax_t number = strtoimax(input, &end, 10);

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

    if (printf("%s\n",
               is_difference_of_two_squares(number) ? "Yes" : "No") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}