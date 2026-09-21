#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool starts_with_number(const char *string, long number)
{
    char prefix[sizeof(long) * 3U + 3U];
    int length;

    if (string == NULL || number < 0) {
        return false;
    }

    length = snprintf(prefix, sizeof prefix, "%ld", number);
    if (length < 0 || (size_t)length >= sizeof prefix) {
        return false;
    }

    return strncmp(string, prefix, (size_t)length) == 0;
}

int main(int argc, char * const argv[])
{
    char *end = NULL;
    long number;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number> <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtol(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || number < 0) {
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