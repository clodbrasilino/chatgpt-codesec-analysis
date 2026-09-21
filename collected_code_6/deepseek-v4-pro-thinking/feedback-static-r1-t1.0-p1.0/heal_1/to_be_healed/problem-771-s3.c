#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    CHECK_ERROR = -1,
    CHECK_UNBALANCED = 0,
    CHECK_BALANCED = 1
};

/* Possible weaknesses found:
 * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
 */
static int is_matching_pair(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

int is_balanced(const char *expr)
{
    if (expr == NULL) {
        return CHECK_ERROR;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(expr);
    char *stack = malloc(len + 1);
    if (stack == NULL) {
        return CHECK_ERROR;
    }

    size_t top = 0;

    for (size_t i = 0; i < len; ++i) {
        char c = expr[i];

        if (c == '(' || c == '{' || c == '[') {
            stack[top++] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == 0) {
                free(stack);
                return CHECK_UNBALANCED;
            }

            char open = stack[--top];
            /* Possible weaknesses found:
             * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
             */
            if (!is_matching_pair(open, c)) {
                free(stack);
                return CHECK_UNBALANCED;
            }
        }
    }

    int status = (top == 0) ? CHECK_BALANCED : CHECK_UNBALANCED;
    free(stack);
    return status;
}

int main(void)
{
    const char *expr = "{[()]}";
    int status = is_balanced(expr);

    if (status == CHECK_ERROR) {
        fprintf(stderr, "Error: invalid input or allocation failure\n");
        return EXIT_FAILURE;
    }

    if (status == CHECK_BALANCED) {
        puts("Balanced");
    } else {
        puts("Not balanced");
    }

    return EXIT_SUCCESS;
}