#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isValidParentheses(const char *s) {
    int len = strlen(s);
    char *stack = (char *)malloc(len + 1);
    if (stack == NULL) {
        return false;
    }
    int top = -1;
    
    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            stack[++top] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == -1) {
                free(stack);
                return false;
            }
            char open = stack[top--];
            if ((c == ')' && open != '(') ||
                (c == '}' && open != '{') ||
                (c == ']' && open != '[')) {
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