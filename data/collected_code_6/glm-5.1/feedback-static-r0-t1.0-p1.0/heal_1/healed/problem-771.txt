#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_balanced(const char *expression) {
    if (expression == NULL) {
        return 0;
    }

    size_t len = strnlen(expression, 1024 * 1024);
    char *stack = (char *)malloc(len + 1);
    if (stack == NULL) {
        return 0;
    }

    int top = -1;

    for (size_t i = 0; i < len; i++) {
        char c = expression[i];
        if (c == '(' || c == '{' || c == '[') {
            stack[++top] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == -1) {
                free(stack);
                return 0;
            }
            char matched_open = stack[top--];
            if ((c == ')' && matched_open != '(') ||
                (c == '}' && matched_open != '{') ||
                (c == ']' && matched_open != '[')) {
                free(stack);
                return 0;
            }
        }
    }

    int result = (top == -1) ? 1 : 0;
    free(stack);
    return result;
}

int main(int argc, char * const argv[]) {
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