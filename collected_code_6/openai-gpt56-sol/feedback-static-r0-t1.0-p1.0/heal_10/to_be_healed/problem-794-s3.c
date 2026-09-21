#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    INPUT_CAPACITY = 1024
};

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           length >= 2U &&
           string[0] == 'a' &&
           string[length - 1U] == 'b';
}

static bool discard_line(void)
{
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
    }

    return character == '\n' || !ferror(stdin);
}

int main(void)
{
    char *input = malloc((size_t)INPUT_CAPACITY + 2U);

    if (input == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, INPUT_CAPACITY + 2, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("stdin");
            free(input);
            return EXIT_FAILURE;
        }

        free(input);
        return EXIT_SUCCESS;
    }

    size_t length = strcspn(input, "\r\n");

    if (input[length] == '\r' || input[length] == '\n') {
        input[length] = '\0';
    } else if (length > (size_t)INPUT_CAPACITY) {
        if (!discard_line()) {
            perror("stdin");
            free(input);
            return EXIT_FAILURE;
        }

        fputs("Input too long\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");

    free(input);
    return EXIT_SUCCESS;
}