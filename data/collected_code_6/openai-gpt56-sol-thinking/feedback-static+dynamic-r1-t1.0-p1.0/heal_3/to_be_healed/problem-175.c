#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  */

static bool is_valid_parentheses(const char *string)
{
    size_t depth = 0;

    if (string == NULL) {
        return false;
    }

    for (; *string != '\0'; ++string) {
        switch (*string) {
        case '(':
            if (depth == SIZE_MAX) {
                return false;
            }
            ++depth;
            break;

        case ')':
            if (depth == 0) {
                return false;
            }
            --depth;
            break;

        default:
            return false;
        }
    }

    return depth == 0;
}

int main(int argc, char **argv)
{
    bool valid;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fputs("Usage: parentheses <parentheses>\n", stderr);
        return EXIT_FAILURE;
    }

    valid = is_valid_parentheses(argv[1]);

    if (puts(valid ? "True" : "False") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}