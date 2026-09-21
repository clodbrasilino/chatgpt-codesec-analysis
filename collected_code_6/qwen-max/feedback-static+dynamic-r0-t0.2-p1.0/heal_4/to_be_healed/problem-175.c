#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isValidParentheses(const char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(s);
    if (len % 2 != 0) return false;

    int stack[len];
    int top = -1;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            stack[++top] = s[i];
        } else if (s[i] == ')') {
            if (top == -1 || stack[top--] != '(') {
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

    printf("%s: %s\n", test1, isValidParentheses(test1) ? "True" : "False");
    printf("%s: %s\n", test2, isValidParentheses(test2) ? "True" : "False");
    printf("%s: %s\n", test3, isValidParentheses(test3) ? "True" : "False");
    printf("%s: %s\n", test4, isValidParentheses(test4) ? "True" : "False");
    printf("%s: %s\n", test5, isValidParentheses(test5) ? "True" : "False");

    return 0;
}