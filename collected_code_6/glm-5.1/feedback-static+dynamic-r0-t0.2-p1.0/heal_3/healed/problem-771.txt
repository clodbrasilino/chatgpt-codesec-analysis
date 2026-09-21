#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_balanced(const char *expression, size_t len) {
    if (expression == NULL) {
        return 0;
    }

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

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <expression>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = strnlen(argv[1], 1024 * 1024);

    if (is_balanced(argv[1], len)) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }

    return EXIT_SUCCESS;
}