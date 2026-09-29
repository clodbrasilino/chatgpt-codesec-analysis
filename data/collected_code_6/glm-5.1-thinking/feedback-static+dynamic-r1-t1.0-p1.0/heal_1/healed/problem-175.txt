#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_valid_parentheses(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t capacity = 16;
    char *stack = malloc(capacity);
    if (stack == NULL) {
        return false;
    }

    size_t top = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        char c = str[i];
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
            char popped = stack[--top];
            if ((c == ')' && popped != '(') ||
                (c == ']' && popped != '[') ||
                (c == '}' && popped != '{')) {
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
        "([])",
        "{[()]}",
        "([)]",
        "(()",
        ")(",
        "",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        printf("'%s': %s\n", test_cases[i], is_valid_parentheses(test_cases[i]) ? "Valid" : "Invalid");
    }

    return 0;
}