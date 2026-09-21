#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_balanced(const char *expression) {
    if (expression == NULL) {
        return 0;
    }

    size_t len = strnlen(expression, 1024 * 1024);
    char *stack = (char *)malloc(len == 0 ? 1 : len);
    if (stack == NULL) {
        return 0;
    }

    int top = -1;

    for (size_t i = 0; i < len; i++) {
        char c = expression[i];
        if (c == '(' || c == '{' || c == '[') {
            top++;
            if ((size_t)top >= len) {
                free(stack);
                return 0;
            }
            stack[top] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == -1) {
                free(stack);
                return 0;
            }
            char matched_open = stack[top];
            top--;
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

    size_t argv1_len = strnlen(argv[1], 1024 * 1024);
    size_t safe_arg_size = argv1_len + 1;
    char *safe_arg = (char *)malloc(safe_arg_size);
    if (safe_arg == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    memcpy(safe_arg, argv[1, safe_arg_size);

    if (is_balanced(safe_arg)) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }

    free(safe_arg);
    return 0;
}