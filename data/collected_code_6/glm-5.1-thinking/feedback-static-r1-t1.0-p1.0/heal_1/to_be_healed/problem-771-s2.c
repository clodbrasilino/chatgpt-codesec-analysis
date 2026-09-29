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
    size_t len = strlen(expr);
    char *stack = malloc(len * sizeof(char));
    if (stack == NULL) {
        return 0;
    }

    int top = -1;

    for (size_t i = 0; i < len; i++) {
        char ch = expr[i];
        if (ch == '(' || ch == '[' || ch == '{') {
            top++;
            stack[top] = ch;
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (top == -1) {
                free(stack);
                return 0;
            }
            char open = stack[top];
            top--;
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

    int balanced = (top == -1) ? 1 : 0;
    free(stack);
    return balanced;
}

int main(int argc, char *argv[]) {
    const char *expr1 = "([{}])";
    const char *expr2 = "([)]";
    const char *expr3 = "(((()";
    const char *expr4 = NULL;

    printf("Expression 1: %d\n", isBalanced(expr1));
    printf("Expression 2: %d\n", isBalanced(expr2));
    printf("Expression 3: %d\n", isBalanced(expr3));
    printf("Expression 4: %d\n", isBalanced(expr4));

    return 0;
}