#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool starts_with_number(const char *string, long number)
{
    if (string == NULL || number < 0) {
        return false;
    }

    int length = snprintf(NULL, 0, "%ld", number);
    if (length < 0) {
        return false;
    }

    size_t size = (size_t)length + 1;
    char *prefix = malloc(size);
    if (prefix == NULL) {
        return false;
    }

    int written = snprintf(prefix, size, "%ld", number);
    if (written != length) {
        free(prefix);
        return false;
    }

    bool matches = true;

    for (size_t i = 0; i < (size_t)length; ++i) {
        if (string[i] == '\0' || string[i] != prefix[i]) {
            matches = false;
            break;
        }
    }

    free(prefix);
    return matches;
}

int main(int argc, char *argv[])
{
    const char *program_name =
        argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Usage: %s <number> <string>\n", program_name);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    long number = strtol(argv[1], &end, 10);

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