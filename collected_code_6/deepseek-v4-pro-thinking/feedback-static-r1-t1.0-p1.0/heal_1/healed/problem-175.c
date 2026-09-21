#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

bool isValidParentheses(const char *s) {
    if (s == NULL) {
        return false;
    }

    size_t capacity = 16;
    char *stack = malloc(capacity);
    if (stack == NULL) {
        return false;
    }

    size_t top = 0;

    for (const char *p = s; *p != '\0'; p++) {
        char c = *p;
        if (c == '(' || c == '[' || c == '{') {
            if (top == capacity) {
                size_t new_capacity = capacity * 2;
                char *new_stack = realloc(stack, new_capacity);
                if (new_stack == NULL) {
                    free(stack);
                    return false;
                }
                stack = new_stack;
                capacity = new_capacity;
            }
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