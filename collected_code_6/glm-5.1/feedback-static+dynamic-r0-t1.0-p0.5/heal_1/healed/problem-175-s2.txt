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
        char current = str[i];
        if (current == '(' || current == '{' || current == '[') {
            stack[top++] = current;
        } else if (current == ')' || current == '}' || current == ']') {
            if (top == 0) {
                free(stack);
                return 0;
            }
            char match = stack[--top];
            if ((current == ')' && match != '(') ||
                (current == '}' && match != '{') ||
                (current == ']' && match != '[')) {
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
    const char *tests[] = {
        "()",
        "({[]})",
        "(]",
        "([)]",
        "",
        "(((())))",
        NULL
    };

    for (int i = 0; tests[i] != NULL; i++) {
        printf("'%s': %s\n", tests[i], verify_parentheses(tests[i]) ? "Valid" : "Invalid");
    }

    return 0;
}