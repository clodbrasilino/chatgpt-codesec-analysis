#include <stdbool.h>
#include <stdint.h>
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
    int c = EOF;

    while ((c = fgetc(stdin)) != EOF && c != '\n') {
        if (length == SIZE_MAX - 1) {
            free(input);
            fputs("Input too large\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 16;
            } else if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
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

        input[length++] = (char)(unsigned char)c;
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