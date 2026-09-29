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
        char ch = expression[i];
        if (ch == '(' || ch == '{' || ch == '[') {
            stack[++top] = ch;
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (top == -1) {
                free(stack);
                return 0;
            }
            char popped = stack[top--];
            if ((ch == ')' && popped != '(') ||
                (ch == '}' && popped != '{') ||
                (ch == ']' && popped != '[')) {
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

    /* Possible weaknesses found:
     *  did you mean 'strnlen'?
     *  implicit declaration of function 'strnlen_s'; did you mean 'strnlen'? [-Wimplicit-function-declaration]
     *  call to undeclared function 'strnlen_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    size_t len = strnlen_s(argv[1], 1024);
    if (len == 1024) {
        fprintf(stderr, "Error: String is not null-terminated within bounds\n");
        return 1;
    }

    if (is_balanced(argv[1], len)) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }

    return 0;
}