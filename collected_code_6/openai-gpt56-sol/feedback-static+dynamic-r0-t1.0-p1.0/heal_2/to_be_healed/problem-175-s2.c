#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 2 failed: expected True, got <no output>
  */

static bool is_valid_parentheses(const char *str)
{
    if (str == NULL) {
        return false;
    }

    size_t balance = 0;

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
    char *line = malloc(capacity);

    if (line == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stream)) {
                free(line);
                return NULL;
            }

            if (ch == EOF && length == 0) {
                free(line);
                return NULL;
            }

            line[length] = '\0';
            return line;
        }

        if (length + 1 >= capacity) {
            if (capacity > (size_t)-1 / 2) {
                free(line);
                return NULL;
            }

            size_t new_capacity = capacity * 2;
            char *resized = realloc(line, new_capacity);

            if (resized == NULL) {
                free(line);
                return NULL;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }
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

    bool valid = is_valid_parentheses(input);
    free(input);

    if (printf("%s\n", valid ? "Valid" : "Invalid") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}