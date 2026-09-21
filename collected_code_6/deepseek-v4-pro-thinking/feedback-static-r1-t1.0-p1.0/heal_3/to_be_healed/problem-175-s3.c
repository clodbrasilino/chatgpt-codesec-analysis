#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isValid(const char *s, size_t len) {
    if (s == NULL) {
        return false;
    }

    if (len % 2 != 0) {
        return false;
    }

    if (len == 0) {
        return true;
    }

    char *stack = malloc(len);
    if (stack == NULL) {
        return false;
    }

    size_t top = 0;

    for (size_t i = 0; i < len; i++) {
        char c = s[i];

        if (c == '(' || c == '[' || c == '{') {
            stack[top++] = c;
        } else if (c == ')' || c == ']' || c == '}') {
            if (top == 0) {
                free(stack);
                return false;
            }

            char expected = stack[--top];

            if ((c == ')' && expected != '(') ||
                (c == ']' && expected != '[') ||
                (c == '}' && expected != '{')) {
                free(stack);
                return false;
            }
        } else {
            free(stack);
            return false;
        }
    }

    bool valid = (top == 0);
    free(stack);
    return valid;
}

int main(void) {
    const char *tests[] = {
        "()",
        "()[]{}",
        "(]",
        "([)]",
        "{[]}",
        "(((",
        "",
        NULL
    };

    for (int i = 0; tests[i] != NULL; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(tests[i]);
        printf("%s: %s\n", tests[i], isValid(tests[i], len) ? "valid" : "invalid");
    }

    return 0;
}