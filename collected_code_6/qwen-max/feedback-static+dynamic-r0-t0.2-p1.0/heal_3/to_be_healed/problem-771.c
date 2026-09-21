#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isBalanced(const char *expression, size_t len) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char stack[len];
    int top = -1;

    for (size_t i = 0; i < len; i++) {
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

    for (size_t i = 0; i < sizeof(expressions) / sizeof(expressions[0]); i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(expressions[i]);
        printf("%s: %s\n", expressions[i], isBalanced(expressions[i], len) ? "Balanced" : "Not Balanced");
    }

    return 0;
}