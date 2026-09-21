#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_balanced(const char *expression, size_t length) {
    if (expression == NULL || length == 0) {
        return 0;
    }

    char *stack = (char *)malloc(length);
    if (stack == NULL) {
        return 0;
    }

    size_t top = 0;

    for (size_t i = 0; i < length; i++) {
        char current = expression[i];
        if (current == '\0') {
            break;
        }
        if (current == '(' || current == '{' || current == '[') {
            stack[top++] = current;
        } else if (current == ')' || current == '}' || current == ']') {
            if (top == 0) {
                free(stack);
                return 0;
            }
            char popped = stack[--top];
            if ((current == ')' && popped != '(') ||
                (current == '}' && popped != '{') ||
                (current == ']' && popped != '[')) {
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
        fprintf(stderr, "Usage: %s <expression>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *expr = argv[1];
    size_t len = 0;
    while (len < (size_t)-1 && expr[len] != '\0') {
        len++;
    }

    if (is_balanced(expr, len)) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }

    return EXIT_SUCCESS;
}