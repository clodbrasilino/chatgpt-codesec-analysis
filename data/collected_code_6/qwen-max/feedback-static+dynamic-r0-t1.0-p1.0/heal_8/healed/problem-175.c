#include <stdio.h>
#include <stdbool.h>

bool isValidParentheses(const char* s, size_t len) {
    if (len % 2 != 0) return false;

    int stack[len];
    int top = -1;

    for (size_t i = 0; i < len; i++) {
        if (s[i] == '(') {
            stack[++top] = i;
        } else if (s[i] == ')') {
            if (top == -1) return false;
            --top;
        }
    }

    return top == -1;
}

int main() {
    const char* test1 = "()";
    const char* test2 = "(()())";
    const char* test3 = "(()";
    const char* test4 = "())(";

    printf("%s: %s\n", test1, isValidParentheses(test1, sizeof(test1) - 1) ? "Valid" : "Invalid");
    printf("%s: %s\n", test2, isValidParentheses(test2, sizeof(test2) - 1) ? "Valid" : "Invalid");
    printf("%s: %s\n", test3, isValidParentheses(test3, sizeof(test3) - 1) ? "Valid" : "Invalid");
    printf("%s: %s\n", test4, isValidParentheses(test4, sizeof(test4) - 1) ? "Valid" : "Invalid");

    return 0;
}