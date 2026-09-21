#include <stdio.h>
#include <stdlib.h>

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int is_balanced(const char *expression) {
    if (expression == NULL) {
        return 0;
    }

    size_t len = safe_strlen(expression, 1024 * 1024);
    char *stack = (char *)malloc(len + 1);
    if (stack == NULL) {
        return 0;
    }

    int top = -1;

    for (size_t i = 0; i < len; i++) {
        char current = expression[i];
        if (current == '(' || current == '{' || current == '[') {
            stack[++top] = current;
        } else if (current == ')' || current == '}' || current == ']') {
            if (top == -1) {
                free(stack);
                return 0;
            }
            char match = stack[top--];
            if ((current == ')' && match != '(') ||
                (current == '}' && match != '{') ||
                (current == ']' && match != '[')) {
                free(stack);
                return 0;
            }
        }
    }

    int result = (top == -1) ? 1 : 0;
    free(stack);
    return result;
}

int main(int argc, char *const argv[]) {
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