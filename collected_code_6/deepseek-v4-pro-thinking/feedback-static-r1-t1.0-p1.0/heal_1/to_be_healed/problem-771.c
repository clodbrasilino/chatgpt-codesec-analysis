#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isBalanced(const char *expr) {
    if (expr == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(expr);
    char *stack = malloc(length + 1);
    if (stack == NULL) {
        return -1;
    }

    size_t top = 0;

    for (size_t i = 0; expr[i] != '\0'; ++i) {
        char ch = expr[i];

        if (ch == '(' || ch == '[' || ch == '{') {
            stack[top] = ch;
            ++top;
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (top == 0) {
                free(stack);
                return 0;
            }

            --top;
            char open = stack[top];

            /* Possible weaknesses found:
             * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
             */
            if ((ch == ')' && open != '(') ||
                /* Possible weaknesses found:
                 * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
                 */
                (ch == ']' && open != '[') ||
                /* Possible weaknesses found:
                 * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
                 */
                (ch == '}' && open != '{')) {
                free(stack);
                return 0;
            }
        }
    }

    int balanced = (top == 0) ? 1 : 0;
    free(stack);
    return balanced;
}

int main(void) {
    const char *tests[] = {
        "",
        "()",
        "()[]{}",
        "(]",
        "([{}])",
        "({[})",
        "(((",
        ")))",
        "a+b*(c-d)",
        NULL
    };

    for (size_t i = 0; tests[i] != NULL; ++i) {
        int result = isBalanced(tests[i]);

        if (result == -1) {
            printf("\"%s\": memory allocation failed\n", tests[i]);
        } else {
            printf("\"%s\": %s\n", tests[i], result == 1 ? "balanced" : "not balanced");
        }
    }

    return 0;
}