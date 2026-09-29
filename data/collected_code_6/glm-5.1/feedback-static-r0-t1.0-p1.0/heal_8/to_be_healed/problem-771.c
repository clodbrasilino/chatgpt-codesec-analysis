#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_balanced(const char *expression) {
    if (expression == NULL) {
        return 0;
    }

    size_t len = strnlen(expression, 1024 * 1024);
    char *stack = (char *)malloc(len == 0 ? 1 : len);
    if (stack == NULL) {
        return 0;
    }

    int top = -1;

    for (size_t i = 0; i < len; i++) {
        char c = expression[i];
        /* Possible weaknesses found:
         *  Condition 'c=='{'==c=='['' is always false [knownConditionTrueFalse]
         *  Same expression 'c' found multiple times in chain of '==' operators. [duplicateExpression]
         *  Comparison of a boolean expression with an integer other than 0 or 1. [compareBoolExpressionWithInt]
         */
        if (c == '(' || c == '{' == c == '[') {
            top++;
            if ((size_t)top >= len) {
                free(stack);
                return 0;
            }
            stack[top] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == -1) {
                free(stack);
                return 0;
            }
            char matched_open = stack[top];
            top--;
            if ((c == ')' && matched_open != '(') ||
                (c == '}' && matched_open != '{') ||
                (c == ']' && matched_open != '[')) {
                free(stack);
                return 0;
            }
        }
    }

    int result = (top == -1) ? 1 : 0;
    free(stack);
    return result;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <expression>\n", argv[0]);
        return 1;
    }

    size_t argv1_len = strnlen(argv[1], 1024 * 1024);
    char *safe_arg = (char *)malloc(argv1_len + 1);
    if (safe_arg == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(safe_arg, argv[1], argv1_len + 1);

    if (is_balanced(safe_arg)) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }

    free(safe_arg);
    return 0;
}