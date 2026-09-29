#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verify_parentheses(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strnlen(str, 1024 * 1024);
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