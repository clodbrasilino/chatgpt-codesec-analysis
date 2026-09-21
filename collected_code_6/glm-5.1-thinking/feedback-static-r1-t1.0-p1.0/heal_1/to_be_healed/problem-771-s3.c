#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isBalanced(const char *expression) {
    if (expression == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(expression);
    if (len == 0) {
        return true;
    }

    char *stack = (char *)malloc(len);
    if (stack == NULL) {
        return false;
    }

    bool status = true;
    int top = -1;

    for (size_t i = 0; i < len; i++) {
        char current = expression[i];

        if (current == '(' || current == '{' || current == '[') {
            stack[++top] = current;
        } else if (current == ')' || current == '}' || current == ']') {
            if (top < 0) {
                status = false;
                break;
            }

            char open = stack[top--];

            /* Possible weaknesses found:
             * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
             */
            if ((current == ')' && open != '(') ||
                /* Possible weaknesses found:
                 * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
                 */
                (current == '}' && open != '{') ||
                /* Possible weaknesses found:
                 * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
                 */
                (current == ']' && open != '[')) {
                status = false;
                break;
            }
        }
    }

    if (top != -1) {
        status = false;
    }

    free(stack);
    return status;
}

int main(void) {
    const char *expressions[] = {
        "{[()]}",
        "{[(])}",
        "({[]})}",
        "",
        NULL
    };

    size_t count = sizeof(expressions) / sizeof(expressions[0]);

    for (size_t i = 0; i < count; i++) {
        const char *exp = expressions[i];
        if (exp == NULL) {
            printf("NULL : Not Balanced\n");
        } else {
            printf("%s : %s\n", exp, isBalanced(exp) ? "Balanced" : "Not Balanced");
        }
    }

    return 0;
}