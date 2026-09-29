#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 4096U

static bool contains_only_allowed_characters(const char *string)
{
    const unsigned char *p;

    if (string == NULL || *string == '\0') {
        return false;
    }

    p = (const unsigned char *)string;

    while (*p != '\0') {
        if (!((*p >= (unsigned char)'A' && *p <= (unsigned char)'Z') ||
              (*p >= (unsigned char)'a' && *p <= (unsigned char)'z') ||
              (*p >= (unsigned char)'0' && *p <= (unsigned char)'9'))) {
            return false;
        }
        ++p;
    }

    return true;
}

static int discard_line(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ferror(stdin) ? -1 : 0;
}

int main(void)
{
    char *input;
    size_t length = 0U;
    int result = EXIT_SUCCESS;

    input = malloc(MAX_INPUT_LENGTH + 2U);
    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)(MAX_INPUT_LENGTH + 2U), stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            result = EXIT_FAILURE;
        } else {
            puts("invalid");
        }

        free(input);
        return result;
    }

    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        if (discard_line() != 0) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Input is too large.\n", stderr);
        }

        free(input);
        return EXIT_FAILURE;
    }

    puts(contains_only_allowed_characters(input) ? "valid" : "invalid");

    free(input);
    return EXIT_SUCCESS;
}