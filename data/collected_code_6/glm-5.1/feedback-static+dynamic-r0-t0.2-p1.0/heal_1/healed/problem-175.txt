#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verify_parentheses(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strnlen(str, 1024 * 1024);
    size_t capacity = len > 0 ? len : 1;
    char *stack = (char *)malloc(capacity);
    if (stack == NULL) {
        return 0;
    }

    size_t top = 0;

    for (size_t i = 0; i < len; i++) {
        char c = str[i];
        if (c == '(' || c == '{' || c == '[') {
            if (top >= capacity) {
                free(stack);
                return 0;
            }
            stack[top++] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == 0) {
                free(stack);
                return 0;
            }
            char popped = stack[--top];
            if ((c == ')' && popped != '(') ||
                (c == '}' && popped != '{') ||
                (c == ']' && popped != '[')) {
                free(stack);
                return 0;
            }
        }
    }

    int result = (top == 0);
    free(stack);
    return result;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    if (verify_parentheses(argv[1])) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }

    return 0;
}