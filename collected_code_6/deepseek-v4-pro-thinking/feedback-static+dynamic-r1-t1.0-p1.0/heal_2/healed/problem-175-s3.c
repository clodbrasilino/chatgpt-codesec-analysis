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
            char opening = stack[--top];
            if ((c == ')' && opening != '(') ||
                (c == ']' && opening != '[') ||
                (c == '}' && opening != '{')) {
                free(stack);
                return false;
            }
        } else {
            free(stack);
            return false;
        }
    }
    bool valid = top == 0;
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
        size_t length = strlen(tests[i]);
        printf("%s: %s\n", tests[i], isValid(tests[i], length) ? "valid" : "invalid");
    }
    return 0;
}