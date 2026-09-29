#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_balanced(const char *expression, size_t max_len) {
    if (expression == NULL) {
        return 0;
    }

    size_t len = strnlen(expression, max_len);
    if (len == max_len && expression[max_len] != '\0') {
        return 0;
    }

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
            char popped = stack[top--];
            if ((c == ')' && popped != '(') ||
                (c == '}' && popped != '{') ||
                (c == ']' && popped != '[')) {
                free(stack);
                return 0;
            }
        }
    }

    int result = (top == -1) ? 1 : 0;
    free(stack);
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <expression>\n", argv[0]);
        return 1;
    }

    size_t max_len = 1024;
    if (strnlen(argv[1], max_len) >= max_len) {
        fprintf(stderr, "Error: Expression exceeds maximum allowed length\n");
        return 1;
    }

    if (is_balanced(argv[1], max_len)) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }

    return 0;
}