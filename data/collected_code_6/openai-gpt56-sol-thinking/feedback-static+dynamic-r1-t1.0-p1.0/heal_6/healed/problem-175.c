#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_valid_parentheses(const char *string)
{
    size_t depth = 0;

    if (string == NULL) {
        return false;
    }

    while (*string != '\0') {
        if (*string == '(') {
            if (depth == SIZE_MAX) {
                return false;
            }
            ++depth;
        } else if (*string == ')') {
            if (depth == 0) {
                return false;
            }
            --depth;
        }

        ++string;
    }

    return depth == 0;
}

int main(int argc, char *const argv[])
{
    bool valid;

    if (argc != 2 || argv[1] == NULL) {
        fputs("Usage: parentheses <text>\n", stderr);
        return EXIT_FAILURE;
    }

    valid = is_valid_parentheses(argv[1]);

    if (puts(valid ? "True" : "False") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}