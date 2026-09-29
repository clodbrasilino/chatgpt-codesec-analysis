#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_balanced(const char *expression);

bool is_balanced(const char *expression) {
    if (expression == NULL) {
        return false;
    }

    if (expression[0] == '\0') {
        return true;
    }

    size_t capacity = 32;
    char *stack = (char *)malloc(capacity);
    if (stack == NULL) {
        return false;
    }

    size_t top = 0;
    bool balanced = true;

    for (const char *ptr = expression; *ptr != '\0'; ptr++) {
        char ch = *ptr;

        if (ch == '(' || ch == '{' || ch == '[') {
            if (top >= capacity) {
                size_t new_capacity = capacity * 2;
                char *new_stack = (char *)realloc(stack, new_capacity);
                if (new_stack == NULL) {
                    free(stack);
                    return false;
                }
                stack = new_stack;
                capacity = new_capacity;
            }
            stack[top++] = ch;
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (top == 0) {
                balanced = false;
                break;
            }
            char top_ch = stack[--top];
            if ((ch == ')' && top_ch != '(') ||
                (ch == '}' && top_ch != '{') ||
                (ch == ']' && top_ch != '[')) {
                balanced = false;
                break;
            }
        }
    }

    if (top != 0) {
        balanced = false;
    }

    free(stack);
    return balanced;
}

int main(void) {
    const char *expressions[] = {
        "{[()]}",
        "{[(])}",
        "{{[[(())]]}}",
        "",
        "a(b)c",
        ")(",
        NULL
    };
    
    size_t num_expressions = sizeof(expressions) / sizeof(expressions[0]);

    for (size_t i = 0; i < num_expressions; i++) {
        if (is_balanced(expressions[i])) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }

    return 0;
}