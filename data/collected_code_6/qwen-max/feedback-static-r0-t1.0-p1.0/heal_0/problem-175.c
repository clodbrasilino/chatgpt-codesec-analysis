#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isValidParentheses(const char* s) {
    int len = strlen(s);
    if (len % 2 != 0) return false;

    int stack[len];
    int top = -1;

    for (int i = 0; i < len; i++) {
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

    printf("%s: %s\n", test1, isValidParentheses(test1) ? "Valid" : "Invalid");
    printf("%s: %s\n", test2, isValidParentheses(test2) ? "Valid" : "Invalid");
    printf("%s: %s\n", test3, isValidParentheses(test3) ? "Valid" : "Invalid");
    printf("%s: %s\n", test4, isValidParentheses(test4) ? "Valid" : "Invalid");

    return 0;
}