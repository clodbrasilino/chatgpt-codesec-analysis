#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isBalanced(const char *expression) {
    if (expression == NULL) {
        return false;
    }

    size_t capacity = 16;
    size_t top = 0;
    char *stack = malloc(capacity);
    if (stack == NULL) {
        return false;
    }

    bool status = true;

    for (size_t i = 0; expression[i] != '\0'; i++) {
        char current = expression[i];

        if (current == '(' || current == '{' || current == '[') {
            if (top >= capacity) {
                capacity *= 2;
                char *new_stack = realloc(stack, capacity);
                if (new_stack == NULL) {
                    free(stack);
                    return false;
                }
                stack = new_stack;
            }
            stack[top++] = current;
        } else if (current == ')' || current == '}' || current == ']') {
            if (top == 0) {
                status = false;
                break;
            }

            char popped = stack[--top];

            if ((current == ')' && popped != '(') ||
                (current == '}' && popped != '{') ||
                (current == ']' && popped != '[')) {
                status = false;
                break;
            }
        }
    }

    if (top != 0) {
        status = false;
    }

    free(stack);
    return status;
}

int main(void) {
    const char *expressions[] = {
        "{[()]}",
        "{[(])}",
        "({[]})}",
        "",
        NULL
    };

    size_t count = sizeof(expressions) / sizeof(expressions[0]);

    for (size_t i = 0; i < count; i++) {
        const char *exp = expressions[i];
        if (exp == NULL) {
            printf("NULL : Not Balanced\n");
        } else {
            printf("%s : %s\n", exp, isBalanced(exp) ? "Balanced" : "Not Balanced");
        }
    }

    return 0;
}