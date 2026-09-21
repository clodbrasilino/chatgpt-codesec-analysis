#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_valid_parentheses(const char *s) {
    if (s == NULL) {
        return false;
    }

    size_t len = 0;
    while (s[len] != '\0') {
        len++;
    }

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
    bool is_valid = true;

    for (size_t i = 0; i < len; i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            stack[top++] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == 0) {
                is_valid = false;
                break;
            }
            char top_char = stack[--top];
            if ((c == ')' && top_char != '(') ||
                (c == '}' && top_char != '{') ||
                (c == ']' && top_char != '[')) {
                is_valid = false;
                break;
            }
        }
    }

    if (top != 0) {
        is_valid = false;
    }

    free(stack);
    return is_valid;
}

int main(void) {
    const char *test_cases[] = {
        "()",
        "()[]{}",
        "(]",
        "([)]",
        "{[]}",
        "",
        NULL
    };

    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++) {
        bool result = is_valid_parentheses(test_cases[i]);
        printf("%s: %s\n", test_cases[i] ? test_cases[i] : "NULL", result ? "true" : "false");
    }

    return 0;
}