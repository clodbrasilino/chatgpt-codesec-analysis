#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isValid(const char *s) {
    if (s == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s);
    if (len == 0) {
        return true;
    }

    char *stack = (char *)malloc(len * sizeof(char));
    if (stack == NULL) {
        return false;
    }

    size_t top = 0;
    bool valid = true;

    for (size_t i = 0; i < len; i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            stack[top++] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == 0) {
                valid = false;
                break;
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
                valid = false;
                break;
            }
        }
    }

    if (top != 0) {
        valid = false;
    }

    free(stack);
    return valid;
}

int main(void) {
    const char *test1 = "()";
    const char *test2 = "()[]{}";
    const char *test3 = "(]";
    const char *test4 = "([)]";
    const char *test5 = "{[]}";
    const char *test6 = NULL;

    printf("%s: %s\n", test1, isValid(test1) ? "true" : "false");
    printf("%s: %s\n", test2, isValid(test2) ? "true" : "false");
    printf("%s: %s\n", test3, isValid(test3) ? "true" : "false");
    printf("%s: %s\n", test4, isValid(test4) ? "true" : "false");
    printf("%s: %s\n", test5, isValid(test5) ? "true" : "false");
    /* Possible weaknesses found:
     *  Calling function 'isValid' returns 0
     *  Condition 'isValid(test6)' is always false
     *  Condition 'isValid(test6)' is always false [knownConditionTrueFalse]
     */
    printf("NULL: %s\n", isValid(test6) ? "true" : "false");

    return 0;
}