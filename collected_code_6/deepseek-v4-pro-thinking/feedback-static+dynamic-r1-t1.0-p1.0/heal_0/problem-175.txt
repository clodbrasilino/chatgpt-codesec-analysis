#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isValidParentheses(const char *s) {
    if (s == NULL) {
        return false;
    }

    size_t len = strlen(s);
    char *stack = malloc(len + 1);
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

            char open = stack[--top];

            if ((c == ')' && open != '(') ||
                (c == ']' && open != '[') ||
                (c == '}' && open != '{')) {
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
        "",
        "()",
        "()[]{}",
        "(]",
        "([)]",
        "{[]}",
        "(",
        "}",
        NULL
    };

    for (int i = 0; tests[i] != NULL; i++) {
        printf("%s: %s\n", tests[i], isValidParentheses(tests[i]) ? "valid" : "invalid");
    }

    return 0;
}