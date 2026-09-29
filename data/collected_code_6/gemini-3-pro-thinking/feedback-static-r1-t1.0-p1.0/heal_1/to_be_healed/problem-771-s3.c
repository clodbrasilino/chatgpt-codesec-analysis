#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool is_balanced(const char *expression);

bool is_balanced(const char *expression) {
    if (expression == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(expression);
    if (length == 0) {
        return true;
    }

    char *stack = (char *)malloc(length * sizeof(char));
    if (stack == NULL) {
        return false;
    }

    int top = -1;
    bool balanced = true;

    for (size_t i = 0; i < length; i++) {
        char current = expression[i];

        if (current == '(' || current == '{' || current == '[') {
            top++;
            stack[top] = current;
        } else if (current == ')' || current == '}' || current == ']') {
            if (top == -1) {
                balanced = false;
                break;
            }

            char last = stack[top];
            top--;

            if ((current == ')' && last != '(') ||
                (current == '}' && last != '{') ||
                (current == ']' && last != '[')) {
                balanced = false;
                break;
            }
        }
    }

    if (top != -1) {
        balanced = false;
    }

    free(stack);
    stack = NULL;

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