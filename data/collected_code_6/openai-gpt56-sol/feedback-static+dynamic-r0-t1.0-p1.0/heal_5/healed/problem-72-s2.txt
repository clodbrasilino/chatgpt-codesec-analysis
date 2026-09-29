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

static int read_line(char *buffer, size_t size)
{
    if (size < 2 || fgets(buffer, size, stdin) == NULL) {
        return 0;
    }

    size_t length = 0;

    while (length < size && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length < size && buffer[length] == '\n') {
        buffer[length] = '\0';
        return 1;
    }

    int ch = fgetc(stdin);

    if (ch == '\n' || ch == EOF) {
        return 1;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return 0;
}

int main(void)
{
    char input[128];
    char *end;
    intmax_t value;

    if (!read_line(input, sizeof input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
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