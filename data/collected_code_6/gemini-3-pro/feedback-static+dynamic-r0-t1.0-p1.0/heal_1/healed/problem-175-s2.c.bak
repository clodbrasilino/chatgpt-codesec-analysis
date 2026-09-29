#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

bool is_valid_parentheses(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return true;
    }

    char *stack = (char *)malloc(len * sizeof(char));
    if (stack == NULL) {
        return false;
    }

    ptrdiff_t top = -1;

    for (size_t i = 0; i < len; i++) {
        char current_char = str[i];

        if (current_char == '(' || current_char == '{' || current_char == '[') {
            top++;
            stack[top] = current_char;
        } else if (current_char == ')' || current_char == '}' || current_char == ']') {
            if (top == -1) {
                free(stack);
                return false;
            }

            char top_char = stack[top];
            top--;

            if ((current_char == ')' && top_char != '(') ||
                (current_char == '}' && top_char != '{') ||
                (current_char == ']' && top_char != '[')) {
                free(stack);
                return false;
            }
        }
    }

    bool is_valid = (top == -1);
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
        NULL
    };

    for (size_t i = 0; test_cases[i] != NULL; i++) {
        bool result = is_valid_parentheses(test_cases[i]);
        printf("%s: %s\n", test_cases[i], result ? "Valid" : "Invalid");
    }

    return 0;
}