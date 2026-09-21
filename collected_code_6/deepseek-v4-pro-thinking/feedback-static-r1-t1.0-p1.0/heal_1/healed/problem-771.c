#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_INITIAL_CAPACITY 16

int isBalanced(const char *expr, size_t len) {
    if (expr == NULL) {
        return 0;
    }

    size_t capacity = STACK_INITIAL_CAPACITY;
    size_t top = 0;
    char *stack = malloc(capacity);
    if (stack == NULL) {
        return -1;
    }

    for (size_t i = 0; i < len; ++i) {
        char ch = expr[i];

        if (ch == '(' || ch == '[' || ch == '{') {
            if (top >= capacity) {
                size_t new_capacity = capacity * 2;
                char *new_stack = realloc(stack, new_capacity);
                if (new_stack == NULL) {
                    free(stack);
                    return -1;
                }
                stack = new_stack;
                capacity = new_capacity;
            }
            stack[top++] = ch;
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (top == 0) {
                free(stack);
                return 0;
            }

            top--;
            char expected = stack[top];

            if ((ch == ')' && expected != '(') ||
                (ch == ']' && expected != '[') ||
                (ch == '}' && expected != '{')) {
                free(stack);
                return 0;
            }
        }
    }

    int balanced = (top == 0) ? 1 : 0;
    free(stack);
    return balanced;
}

int main(void) {
    const char *tests[] = {
        "",
        "()",
        "()[]{}",
        "(]",
        "([{}])",
        "({[})",
        "(((",
        ")))",
        "a+b*(c-d)",
        NULL
    };

    for (size_t i = 0; tests[i] != NULL; ++i) {
        size_t len = strlen(tests[i]);
        int result = isBalanced(tests[i], len);

        if (result == -1) {
            printf("\"%s\": memory allocation failed\n", tests[i]);
        } else {
            printf("\"%s\": %s\n", tests[i], result == 1 ? "balanced" : "not balanced");
        }
    }

    return 0;
}