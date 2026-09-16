#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isValidParentheses(const char* s) {
    int len = 0;
    while (s[len] != '\0') len++;

    int *stack = (int *)malloc(sizeof(int) * len);
    if (stack == NULL) return false;

    int top = -1;
    for (int i = 0; i < len; ++i) {
        if (s[i] == '(') {
            stack[++top] = s[i];
        } else if (s[i] == ')') {
            if (top == -1 || stack[top--] != '(') {
                free(stack);
                return false;
            }
        }
    }

    bool result = (top == -1);
    free(stack);
    return result;
}

int main() {
    const char* test1 = "(()())";
    const char* test2 = "((())";
    const char* test3 = "()";

    printf("%s: %s\n", test1, isValidParentheses(test1) ? "Valid" : "Invalid");
    printf("%s: %s\n", test2, isValidParentheses(test2) ? "Valid" : "Invalid");
    printf("%s: %s\n", test3, isValidParentheses(test3) ? "Valid" : "Invalid");

    return 0;
}