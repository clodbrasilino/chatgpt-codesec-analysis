#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
    for (size_t i = 0; i < len; i++) {
        char ch = expression[i];
        if (ch == '(' || ch == '{' || ch == '[') {
            stack[top++] = ch;
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (top == 0) {
                free(stack);
                return false;
            }
            
            char last = stack[--top];
            if ((ch == ')' && last != '(') ||
                (ch == '}' && last != '{') ||
                (ch == ']' && last != '[')) {
                free(stack);
                return false;
            }
        }
    }

    bool result = (top == 0);
    free(stack);
    
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "{[()]}",
        "{[(])}",
        "((()))",
        "(()",
        "[]{}()",
        ""
    };

    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (size_t i = 0; i < num_cases; i++) {
        if (is_balanced(test_cases[i])) {
            printf("Balanced\n");
        } else {
            printf("Not Balanced\n");
        }
    }

    return 0;
}