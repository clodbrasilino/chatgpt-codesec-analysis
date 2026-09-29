#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool string_starts_with_number(const char *string, long number)
{
    char *prefix = NULL;
    int prefix_length;
    bool result;

    if (string == NULL) {
        return false;
    }

    prefix_length = snprintf(NULL, 0, "%ld", number);
    if (prefix_length < 0) {
        return false;
    }

    prefix = malloc((size_t)prefix_length + 1U);
    if (prefix == NULL) {
        return false;
    }

    if (snprintf(prefix, (size_t)prefix_length + 1U, "%ld", number) != prefix_length) {
        free(prefix);
        return false;
    }

    result = true;
    for (int i = 0; i < prefix_length; ++i) {
        if (string[i] == '\0' || string[i] != prefix[i]) {
            result = false;
            break;
        }
    }

    free(prefix);
    return result;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    long number;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number> <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtol(argv[1], &end, 10);
    if (errno != 0 || end == argv[1] || *end != '\0') {
        fprintf(stderr, "Invalid number\n");
        return EXIT_FAILURE;
    }

    if (string_starts_with_number(argv[2], number)) {
        puts("The string starts with the specified number.");
    } else {
        puts("The string does not start with the specified number.");
    }

    return EXIT_SUCCESS;
}