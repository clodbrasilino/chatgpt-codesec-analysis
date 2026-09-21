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
    size_t len = strlen(expression);
    if (len == 0) {
        return true;
    }

    char *stack = (char *)malloc(len * sizeof(char));
    if (stack == NULL) {
        return false;
    }

    size_t top = 0;
    bool balanced = true;

    for (size_t i = 0; i < len; i++) {
        char ch = expression[i];

        if (ch == '(' || ch == '{' || ch == '[') {
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