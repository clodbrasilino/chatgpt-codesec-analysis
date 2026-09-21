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
    size_t depth = 0U;

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
            if (depth == 0U) {
                return false;
            }
            --depth;
        } else {
            return false;
        }

        ++string;
    }

    return depth == 0U;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    bool valid;

    if (argc != 2) {
        const char *program_name = argc > 0 && argv[0] != NULL
            ? argv[0]
            : "parentheses";

        fprintf(stderr, "Usage: %s <parentheses>\n", program_name);
        return EXIT_FAILURE;
    }

    valid = is_valid_parentheses(argv[1]);

    if (puts(valid ? "True" : "False") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}