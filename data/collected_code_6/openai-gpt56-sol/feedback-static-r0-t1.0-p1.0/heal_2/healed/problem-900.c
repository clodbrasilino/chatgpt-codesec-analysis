#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool string_starts_with_number(const char *string, long number)
{
    char prefix[sizeof("-") + sizeof(long) * 3U];
    int prefix_length;

    if (string == NULL) {
        return false;
    }

    prefix_length = snprintf(prefix, sizeof(prefix), "%ld", number);
    if (prefix_length < 0 || (size_t)prefix_length >= sizeof(prefix)) {
        return false;
    }

    return strncmp(string, prefix, (size_t)prefix_length) == 0;
}

int main(int argc, const char *argv[])
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

    if (errno == ERANGE || end == argv[1] || *end != '\0') {
        fputs("Invalid number\n", stderr);
        return EXIT_FAILURE;
    }

    if (string_starts_with_number(argv[2], number)) {
        puts("The string starts with the specified number.");
    } else {
        puts("The string does not start with the specified number.");
    }

    return EXIT_SUCCESS;
}