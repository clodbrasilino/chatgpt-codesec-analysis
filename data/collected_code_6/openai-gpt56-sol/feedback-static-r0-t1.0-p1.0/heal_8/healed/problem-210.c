#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char buffer[256];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        if (strchr(buffer, '\n') != NULL) {
            return 0;
        }
    }

    return ferror(stdin) ? -1 : 0;
}

int main(void)
{
    char *input;
    char *newline;
    size_t length;
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

    newline = strchr(input, '\n');
    if (newline != NULL) {
        *newline = '\0';
    } else {
        length = strlen(input);

        if (length > MAX_INPUT_LENGTH) {
            if (discard_line() != 0) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too large.\n", stderr);
            }

            free(input);
            return EXIT_FAILURE;
        }

        if (!feof(stdin)) {
            int ch = fgetc(stdin);

            if (ch == EOF) {
                if (ferror(stdin)) {
                    fputs("Failed to read input.\n", stderr);
                    free(input);
                    return EXIT_FAILURE;
                }
            } else {
                if (ch != '\n' && discard_line() != 0) {
                    fputs("Failed to read input.\n", stderr);
                } else {
                    fputs("Input is too large.\n", stderr);
                }

                free(input);
                return EXIT_FAILURE;
            }
        }
    }

    puts(contains_only_allowed_characters(input) ? "valid" : "invalid");

    free(input);
    return EXIT_SUCCESS;
}