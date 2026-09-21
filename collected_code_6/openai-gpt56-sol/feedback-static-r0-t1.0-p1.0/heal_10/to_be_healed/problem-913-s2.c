#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool ends_with_number(const char *str, size_t length)
{
    return str != NULL &&
           length > 0 &&
           isdigit((unsigned char)str[length - 1]) != 0;
}

int main(void)
{
    const size_t max_input_length = 1024U * 1024U;
    char *input = malloc(max_input_length + 2U);

    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)(max_input_length + 2U), stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        input[0] = '\0';
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > max_input_length) {
        fputs("Input is too large.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    } else if (length == max_input_length) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next = fgetc(stdin);

        if (next != '\n' && next != EOF) {
            fputs("Input is too large.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        if (next == EOF && ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }
    }

    puts(ends_with_number(input, length) ? "true" : "false");

    free(input);
    return EXIT_SUCCESS;
}