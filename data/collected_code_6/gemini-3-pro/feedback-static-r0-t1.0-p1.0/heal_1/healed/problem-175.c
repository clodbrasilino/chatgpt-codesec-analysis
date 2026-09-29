#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isValid(const char *s);

bool isValid(const char *s) {
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
    bool result = true;

    for (size_t i = 0; i < len; i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            stack[top++] = s[i];
        } else if (s[i] == ')' || s[i] == '}' || s[i] == ']') {
            if (top == 0) {
                result = false;
                break;
            }
            char opened_char = stack[--top];
            if ((s[i] == ')' && opened_char != '(') ||
                (s[i] == '}' && opened_char != '{') ||
                (s[i] == ']' && opened_char != '[')) {
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