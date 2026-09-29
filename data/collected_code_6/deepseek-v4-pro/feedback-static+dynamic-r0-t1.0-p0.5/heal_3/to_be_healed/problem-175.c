#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isValidParentheses(const char *s) {
    if (s == NULL) {
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s);
    char *stack = (char *)malloc(len + 1);
    if (stack == NULL) {
        return false;
    }
    int top = -1;
    
    for (size_t i = 0; i < len; i++) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{') {
            stack[++top] = c;
        } else if (c == ')' || c == ']' || c == '}') {
            if (top == -1) {
                free(stack);
                return false;
            }
            char opening = stack[top--];
            if ((c == ')' && opening != '(') ||
                (c == ']' && opening != '[') ||
                (c == '}' && opening != '{')) {
                free(stack);
                return false;
            }
        }
    }
    
    bool result = (top == -1);
    free(stack);
    return result;
}

int main(void) {
    const char *test1 = "()";
    const char *test2 = "()[]{}";
    const char *test3 = "(]";
    const char *test4 = "([)]";
    const char *test5 = "{[]}";
    const char *test6 = "";
    const char *test7 = "(";
    const char *test8 = ")";
    
    printf("%s: %s\n", test1, isValidParentheses(test1) ? "valid" : "invalid");
    printf("%s: %s\n", test2, isValidParentheses(test2) ? "valid" : "invalid");
    printf("%s: %s\n", test3, isValidParentheses(test3) ? "valid" : "invalid");
    printf("%s: %s\n", test4, isValidParentheses(test4) ? "valid" : "invalid");
    printf("%s: %s\n", test5, isValidParentheses(test5) ? "valid" : "invalid");
    printf("%s: %s\n", test6, isValidParentheses(test6) ? "valid" : "invalid");
    printf("%s: %s\n", test7, isValidParentheses(test7) ? "valid" : "invalid");
    printf("%s: %s\n", test8, isValidParentheses(test8) ? "valid" : "invalid");
    
    return 0;
}