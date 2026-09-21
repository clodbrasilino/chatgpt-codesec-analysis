#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_balanced(const char *expression);

bool is_balanced(const char *expression) {
    if (expression == NULL) {
        return false;
    }

    size_t capacity = 32;
    char *stack = (char *)malloc(capacity * sizeof(char));
    if (stack == NULL) {
        return false;
    }

    size_t top = 0;
    bool balanced = true;

    for (size_t i = 0; expression[i] != '\0'; i++) {
        char current = expression[i];

        if (current == '(' || current == '{' || current == '[') {
            if (top >= capacity) {
                size_t new_capacity = capacity * 2;
                char *new_stack = (char *)realloc(stack, new_capacity * sizeof(char));
                if (new_stack == NULL) {
                    free(stack);
                    return false;
                }
                stack = new_stack;
                capacity = new_capacity;
            }
            stack[top++] = current;
        } else if (current == ')' || current == '}' || current == ']') {
            if (top == 0) {
                balanced = false;
                break;
            }

            char last = stack[--top];

            if ((current == ')' && last != '(') ||
                (current == '}' && last != '{') ||
                (current == ']' && last != '[')) {
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
    const char *test_expr1 = "{[()]}";
    const char *test_expr2 = "{[(])}";
    const char *test_expr3 = "((()))";
    const char *test_expr4 = "(()";

    if (is_balanced(test_expr1)) {
        printf("%s is balanced\n", test_expr1);
    } else {
        printf("%s is not balanced\n", test_expr1);
    }

    if (is_balanced(test_expr2)) {
        printf("%s is balanced\n", test_expr2);
    } else {
        printf("%s is not balanced\n", test_expr2);
    }

    if (is_balanced(test_expr3)) {
        printf("%s is balanced\n", test_expr3);
    } else {
        printf("%s is not balanced\n", test_expr3);
    }

    if (is_balanced(test_expr4)) {
        printf("%s is balanced\n", test_expr4);
    } else {
        printf("%s is not balanced\n", test_expr4);
    }

    return EXIT_SUCCESS;
}