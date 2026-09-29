#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_valid_parentheses(const char *s) {
    if (s == NULL) {
        return false;
    }

    if (s[0] == '\0') {
        return true;
    }

    size_t capacity = 32;
    char *stack = (char *)malloc(capacity * sizeof(char));
    if (stack == NULL) {
        return false;
    }

    size_t top = 0;

    for (size_t i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            if (top >= capacity) {
                capacity *= 2;
                char *new_stack = (char *)realloc(stack, capacity * sizeof(char));
                if (new_stack == NULL) {
                    free(stack);
                    return false;
                }
                stack = new_stack;
            }
            stack[top++] = s[i];
        } else if (s[i] == ')' || s[i] == '}' || s[i] == ']') {
            if (top == 0) {
                free(stack);
                return false;
            }
            char popped_char = stack[--top];
            if ((s[i] == ')' && popped_char != '(') ||
                (s[i] == '}' && popped_char != '{') ||
                (s[i] == ']' && popped_char != '[')) {
                free(stack);
                return false;
            }
        } else {
            free(stack);
            return false;
        }
    }

    bool is_valid = (top == 0);
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
        "((",
        "",
        NULL
    };

    for (size_t i = 0; test_cases[i] != NULL; i++) {
        bool result = is_valid_parentheses(test_cases[i]);
        printf("%s: %s\n", test_cases[i][0] == '\0' ? "EMPTY" : test_cases[i], result ? "true" : "false");
    }

    return 0;
}