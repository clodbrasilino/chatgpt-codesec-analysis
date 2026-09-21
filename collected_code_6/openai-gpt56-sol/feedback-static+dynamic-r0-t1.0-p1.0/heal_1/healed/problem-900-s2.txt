#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool starts_with_number(const char *string, long number)
{
    char prefix[sizeof("-9223372036854775808")];
    int length;

    if (string == NULL || number < 0) {
        return false;
    }

    length = snprintf(prefix, sizeof prefix, "%ld", number);
    if (length < 0 || (size_t)length >= sizeof prefix) {
        return false;
    }

    for (size_t i = 0; i < (size_t)length; ++i) {
        if (string[i] == '\0' || string[i] != prefix[i]) {
            return false;
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    char *end;
    long number;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number> <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    number = strtol(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || end == NULL ||
        *end != '\0' || number < 0) {
        fputs("Invalid non-negative number\n", stderr);
        return EXIT_FAILURE;
    }

    if (starts_with_number(argv[2], number)) {
        puts("The string starts with the specified number.");
    } else {
        puts("The string does not start with the specified number.");
    }

    return EXIT_SUCCESS;
}