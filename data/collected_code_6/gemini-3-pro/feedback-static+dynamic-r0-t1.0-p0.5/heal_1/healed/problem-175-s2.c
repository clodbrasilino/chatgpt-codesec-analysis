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

    for (size_t i = 0; i < len; i++) {
        char c = s[i];

        if (c == '(' || c == '{' || c == '[') {
            stack[top++] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == 0) {
                free(stack);
                return false;
            }

            char top_char = stack[--top];
            if ((c == ')' && top_char != '(') ||
                (c == '}' && top_char != '{') ||
                (c == ']' && top_char != '[')) {
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
    const char *test_cases[] = {
        "()",
        "()[]{}",
        "(]",
        "([)]",
        "{[]}",
        NULL
    };

    for (size_t i = 0; test_cases[i] != NULL; i++) {
        bool valid = isValid(test_cases[i]);
        printf("%s: %s\n", test_cases[i], valid ? "true" : "false");
    }

    return 0;
}