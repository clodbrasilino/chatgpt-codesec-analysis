#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_valid_parentheses(const char *str)
{
    size_t balance = 0;

    if (str == NULL) {
        return false;
    }

    for (; *str != '\0'; ++str) {
        if (*str == '(') {
            ++balance;
        } else if (*str == ')') {
            if (balance == 0) {
                return false;
            }
            --balance;
        } else {
            return false;
        }
    }

    return balance == 0;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stream)) {
                free(buffer);
                return NULL;
            }

            if (ch == EOF && length == 0) {
                free(buffer);
                return NULL;
            }

            break;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
        } else if (feof(stdin)) {
            fprintf(stderr, "No input provided.\n");
        } else {
            fprintf(stderr, "Failed to allocate memory.\n");
        }
        return EXIT_FAILURE;
    }

    if (printf("%s\n", is_valid_parentheses(input) ? "Valid" : "Invalid") < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}