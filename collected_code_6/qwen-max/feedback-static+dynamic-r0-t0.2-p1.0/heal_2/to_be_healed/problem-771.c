#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isBalanced(const char *expression, size_t len) {
    int stack[len];
    int top = -1;

    for (int i = 0; i < len; i++) {
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            if (top + 1 >= len) return false;
            stack[++top] = expression[i];
        } else if (expression[i] == ')' || expression[i] == ']' || expression[i] == '}') {
            if (top == -1) return false;
            char last = stack[top--];
            if ((expression[i] == ')' && last != '(') ||
                (expression[i] == ']' && last != '[') ||
                (expression[i] == '}' && last != '{')) {
                return false;
            }
        }
    }

    return top == -1;
}

int main() {
    const char *expressions[] = {
        "([]{})",
        "([)]",
        "{[()]}",
        "{[(])}",
        "{{[[(())]]}}",
        "(()"
    };

    for (int i = 0; i < 6; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(expressions[i]);
        printf("%s: %s\n", expressions[i], isBalanced(expressions[i], len) ? "Balanced" : "Not Balanced");
    }

    return 0;
}