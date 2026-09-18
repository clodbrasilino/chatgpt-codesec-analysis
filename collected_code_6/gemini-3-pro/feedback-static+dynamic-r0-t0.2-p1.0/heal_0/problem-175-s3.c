#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool is_valid_parentheses(const char *s) {
    if (s == NULL) {
        return false;
    }

    size_t len = strlen(s);
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
        } else {
            is_valid = false;
            break;
        }
    }

    if (top != 0) {
        is_valid = false;
    }

    free(stack);
    return is_valid;
}

int main(void) {
    const char *test1 = "()";
    const char *test2 = "()[]{}";
    const char *test3 = "(]";
    const char *test4 = "([)]";
    const char *test5 = "{[]}";
    const char *test6 = NULL;

    printf("%s: %s\n", test1, is_valid_parentheses(test1) ? "true" : "false");
    printf("%s: %s\n", test2, is_valid_parentheses(test2) ? "true" : "false");
    printf("%s: %s\n", test3, is_valid_parentheses(test3) ? "true" : "false");
    printf("%s: %s\n", test4, is_valid_parentheses(test4) ? "true" : "false");
    printf("%s: %s\n", test5, is_valid_parentheses(test5) ? "true" : "false");
    printf("NULL: %s\n", is_valid_parentheses(test6) ? "true" : "false");

    return 0;
}