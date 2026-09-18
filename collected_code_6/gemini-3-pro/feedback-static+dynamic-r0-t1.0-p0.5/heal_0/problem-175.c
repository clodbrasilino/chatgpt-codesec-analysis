#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isValidParentheses(const char *s) {
    if (s == NULL) {
        return false;
    }

    size_t len = strlen(s);
    if (len == 0) {
        return true;
    }

    char *stack = (char *)malloc(len * sizeof(char));
    if (stack == NULL) {
        return false;
    }

    int top = -1;
    bool valid = true;

    for (size_t i = 0; i < len; i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            stack[++top] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == -1) {
                valid = false;
                break;
            }
            char topChar = stack[top--];
            if ((c == ')' && topChar != '(') ||
                (c == '}' && topChar != '{') ||
                (c == ']' && topChar != '[')) {
                valid = false;
                break;
            }
        }
    }

    if (top != -1) {
        valid = false;
    }

    free(stack);
    return valid;
}

int main(void) {
    const char *test1 = "()";
    const char *test2 = "()[]{}";
    const char *test3 = "(]";
    const char *test4 = "([)]";
    const char *test5 = "{[]}";

    printf("%s: %s\n", test1, isValidParentheses(test1) ? "true" : "false");
    printf("%s: %s\n", test2, isValidParentheses(test2) ? "true" : "false");
    printf("%s: %s\n", test3, isValidParentheses(test3) ? "true" : "false");
    printf("%s: %s\n", test4, isValidParentheses(test4) ? "true" : "false");
    printf("%s: %s\n", test5, isValidParentheses(test5) ? "true" : "false");

    return 0;
}