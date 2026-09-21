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

int main(void)
{
    char *input = malloc((size_t)INPUT_CAPACITY + 2U);

    if (input == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return 1;
    }

    if (fgets(input, INPUT_CAPACITY + 2, stdin) == NULL) {
        if (ferror(stdin)) {
            perror("stdin");
            free(input);
            return 1;
        }

        free(input);
        return 0;
    }

    size_t length = strcspn(input, "\r\n");

    if (input[length] == '\r' || input[length] == '\n') {
        input[length] = '\0';
    } else if (length > INPUT_CAPACITY) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != '\r' && ch != EOF);

        if (ferror(stdin)) {
            perror("stdin");
            free(input);
            return 1;
        }

        fputs("Input too long\n", stderr);
        free(input);
        return 1;
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");

    free(input);
    return 0;
}