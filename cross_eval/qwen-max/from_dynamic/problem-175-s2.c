#include <stdio.h>
#include <stdbool.h>

bool isValidParentheses(const char *s) {
    int len = 0;
    while (s[len] != '\0') len++;
    if (len % 2 != 0) return false;

    int stack[len];
    int top = -1;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            if (top < len - 1) {
                stack[++top] = 1;
            } else {
                return false;
            }
        } else if (s[i] == ')') {
            if (top >= 0 && stack[top] == 1) {
                top--;
            } else {
                return false;
            }
        }
    }

    return top == -1;
}

int main() {
    const char *test1 = "()";
    const char *test2 = "(()())";
    const char *test3 = ")(";
    const char *test4 = "(()";

    printf("%s: %s\n", test1, isValidParentheses(test1) ? "true" : "false");
    printf("%s: %s\n", test2, isValidParentheses(test2) ? "true" : "false");
    printf("%s: %s\n", test3, isValidParentheses(test3) ? "true" : "false");
    printf("%s: %s\n", test4, isValidParentheses(test4) ? "true" : "false");

    return 0;
}