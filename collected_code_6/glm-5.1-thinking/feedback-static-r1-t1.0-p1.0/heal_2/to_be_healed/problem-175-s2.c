#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_valid_parentheses(const char *str) {
    if (str == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    char *stack = malloc(len + 1);
    if (stack == NULL) {
        return false;
    }

    size_t top = 0;

    for (size_t i = 0; i < len; i++) {
        char c = str[i];
        if (c == '(' || c == '{' || c == '[') {
            stack[top++] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == 0) {
                free(stack);
                return false;
            }
            char popped = stack[--top];
            if ((c == ')' && popped != '(') ||
                (c == '}' && popped != '{') ||
                (c == ']' && popped != '[')) {
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
    printf("%d\n", is_valid_parentheses("()[]{}"));
    printf("%d\n", is_valid_parentheses("([)]"));
    printf("%d\n", is_valid_parentheses(NULL));
    printf("%d\n", is_valid_parentheses("("));
    printf("%d\n", is_valid_parentheses(")"));
    return 0;
}