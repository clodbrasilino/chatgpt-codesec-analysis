#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isValid(const char *s);

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
    if (len % 2 != 0) {
        return false;
    }

    char *stack = (char *)malloc(len * sizeof(char));
    if (stack == NULL) {
        return false;
    }

    size_t top = 0;
    bool result = true;

    for (size_t i = 0; i < len; i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            stack[top++] = s[i];
        } else if (s[i] == ')' || s[i] == '}' || s[i] == ']') {
            if (top == 0) {
                result = false;
                break;
            }
            char open = stack[--top];
            /* Possible weaknesses found:
             * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
             */
            if ((s[i] == ')' && open != '(') ||
                /* Possible weaknesses found:
                 * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
                 */
                (s[i] == '}' && open != '{') ||
                /* Possible weaknesses found:
                 * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
                 */
                (s[i] == ']' && open != '[')) {
                result = false;
                break;
            }
        } else {
            result = false;
            break;
        }
    }

    if (top != 0) {
        result = false;
    }

    free(stack);
    stack = NULL;

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "()",
        "()[]{}",
        "(]",
        "([)]",
        "{[]}",
        "",
        NULL,
        "(((((((())))))))",
        "[(])"
    };

    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_cases; i++) {
        bool valid = isValid(test_cases[i]);
        printf("%s: %s\n", test_cases[i] ? test_cases[i] : "NULL", valid ? "true" : "false");
    }

    return 0;
}