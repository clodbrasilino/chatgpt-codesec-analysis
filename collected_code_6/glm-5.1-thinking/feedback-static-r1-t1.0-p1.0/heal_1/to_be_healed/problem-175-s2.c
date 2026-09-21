#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_valid_parentheses(const char *str) {
    if (str == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    /* Possible weaknesses found:
     *  Condition 'len+1==0' is always false [knownConditionTrueFalse]
     */
    if (len + 1 == 0) {
        return false;
    }

    char *stack = malloc(len + 1);
    if (stack == NULL) {
        return false;
    }

    size_t top = 0;

    for (size_t i = 0; i < len; i++) {
        char c = str[i];
        if (c == '(' || c == '{' || c == '[') {
            stack[top++] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == 0) {
                free(stack);
                return false;
            }
            char open = stack[--top];
            /* Possible weaknesses found:
             * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
             */
            if ((c == ')' && open != '(') ||
                /* Possible weaknesses found:
                 * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
                 */
                (c == '}' && open != '{') ||
                /* Possible weaknesses found:
                 * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
                 */
                (c == ']' && open != '[')) {
                free(stack);
                return false;
            }
        }
    }

    bool result = (top == 0);
    free(stack);
    return result;
}

int main(void) {
    printf("%d\n", is_valid_parentheses("()[]{}"));
    printf("%d\n", is_valid_parentheses("([)]"));
    printf("%d\n", is_valid_parentheses(NULL));
    printf("%d\n", is_valid_parentheses("("));
    printf("%d\n", is_valid_parentheses(")"));
    return 0;
}