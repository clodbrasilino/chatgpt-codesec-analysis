#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isValidParentheses(const char *s) {
    int len = 0;
    while (s[len] != '\0') len++;
    if (len % 2 != 0) return false;

    int *stack = (int*)malloc(len * sizeof(int));
    if (stack == NULL) return false;
    int top = -1;

    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] == '(') {
            stack[++top] = s[i];
        } else if (s[i] == ')') {
            if (top == -1 || stack[top] != '(') {
                free(stack);
                return false;
            }
            top--;
        }
    }

    bool result = (top == -1);
    free(stack);
    return result;
}

int main() {
    const char *testCases[] = {"()", "()()", "(())", "(()", "())", "(()))(", ""};
    int n = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < n; ++i) {
        printf("%s: %s\n", testCases[i], isValidParentheses(testCases[i]) ? "Valid" : "Invalid");
    }

    return 0;
}