#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool matches(const char *string)
{
    return string != NULL &&
           (strcmp(string, "a") == 0 || strcmp(string, "ab") == 0);
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length >= 2) {
            while (character != '\n' && character != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = fgetc(stdin);
            }

            free(input);

            if (ferror(stdin)) {
                perror("fgetc");
            } else {
                fputs("Input is too long\n", stderr);
            }

            return 1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 4 : capacity * 2;
            char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                free(input);
                fputs("Memory allocation failed\n", stderr);
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(input);
        perror("fgetc");
        return 1;
    }

    if (character == EOF && length == 0) {
        free(input);
        return 0;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return 1;
        }
    }

    input[length] = '\0';
    puts(matches(input) ? "Match" : "No match");

    free(input);
    return 0;
}