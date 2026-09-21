#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verify_parentheses(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    char *stack = (char *)malloc(len + 1);
    if (stack == NULL) {
        return 0;
    }

    size_t top = 0;

    for (size_t i = 0; i < len; i++) {
        char ch = str[i];
        if (ch == '(' || ch == '[' || ch == '{') {
            stack[top++] = ch;
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (top == 0) {
                free(stack);
                return 0;
            }
            char expected_open = stack[--top];
            if ((ch == ')' && expected_open != '(') ||
                (ch == ']' && expected_open != '[') ||
                (ch == '}' && expected_open != '{')) {
                free(stack);
                return 0;
            }
        }
    }

    int result = (top == 0);
    free(stack);
    return result;
}

int main(void) {
    const char *test1 = "([{}])";
    const char *test2 = "([)]";
    const char *test3 = "(((()";
    const char *test4 = NULL;
    
    printf("%d\n", verify_parentheses(test1));
    printf("%d\n", verify_parentheses(test2));
    printf("%d\n", verify_parentheses(test3));
    printf("%d\n", verify_parentheses(test4));

    return 0;
}