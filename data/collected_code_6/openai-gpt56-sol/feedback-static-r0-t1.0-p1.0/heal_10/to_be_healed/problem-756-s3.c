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
    int c;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stdin)) != '\n' && c != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 16 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Input too large\n", stderr);
                return EXIT_FAILURE;
            }

            char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                free(input);
                perror("realloc");
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)c;
    }

    if (c == EOF && ferror(stdin)) {
        free(input);
        perror("fgetc");
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);

        if (input == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    puts(matches(input) ? "Match" : "No match");

    free(input);
    return EXIT_SUCCESS;
}