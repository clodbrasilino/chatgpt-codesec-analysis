#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_balanced(const char *expression) {
    if (expression == NULL) {
        return 0;
    }

    size_t len = strnlen(expression, 1024);
    if (len == 1024) {
        return 0;
    }

    char *stack = (char *)malloc(len + 1);
    if (stack == NULL) {
        return 0;
    }

    int top = -1;

    for (size_t i = 0; i < len; i++) {
        char ch = expression[i];
        if (ch == '(' || ch == '{' || ch == '[') {
            if (top < (int)len) {
                stack[++top] = ch;
            }
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (top == -1) {
                free(stack);
                return 0;
            }
            char matched_opening = stack[top--];
            if ((ch == ')' && matched_opening != '(') ||
                (ch == '}' && matched_opening != '{') ||
                (ch == ']' && matched_opening != '[')) {
                free(stack);
                return 0;
            }
        }
    }

    int result = (top == -1) ? 1 : 0;
    free(stack);
    return result;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <expression>\n", argv[0]);
        return 1;
    }

    if (is_balanced(argv[1])) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }

    return 0;
}