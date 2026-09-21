#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 2 failed: expected True, got <no output>
  */

bool isValidParentheses(const char *s) {
    int len = 0;
    while (s[len] != '\0') {
        if (s[len] == '(' || s[len] == ')') {
            len++;
        } else {
            return false;
        }
    }
    if (len % 2 != 0) return false;

    int stack[len];
    int top = -1;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            stack[++top] = 1;
        } else if (s[i] == ')') {
            if (top == -1 || stack[top--] != 1) {
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
    const char *test4 = "(())";
    const char *test5 = "(()";

    printf("%s: %s\n", test1, isValidParentheses(test1) ? "Valid" : "Invalid");
    printf("%s: %s\n", test2, isValidParentheses(test2) ? "Valid" : "Invalid");
    printf("%s: %s\n", test3, isValidParentheses(test3) ? "Valid" : "Invalid");
    printf("%s: %s\n", test4, isValidParentheses(test4) ? "Valid" : "Invalid");
    printf("%s: %s\n", test5, isValidParentheses(test5) ? "Valid" : "Invalid");

    return 0;
}