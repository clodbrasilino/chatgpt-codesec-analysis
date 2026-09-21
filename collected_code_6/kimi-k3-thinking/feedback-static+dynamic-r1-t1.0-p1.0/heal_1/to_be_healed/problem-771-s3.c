#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isBalanced(const char *expression)
{
    if (expression == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(expression);
    if (length == 0) {
        return 1;
    }

    char *stack = malloc(length);
    if (stack == NULL) {
        return -1;
    }

    size_t top = 0;
    int balanced = 1;

    for (size_t i = 0; i < length; i++) {
        char ch = expression[i];

        if (ch == '(' || ch == '[' || ch == '{') {
            stack[top] = ch;
            top++;
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (top == 0) {
                balanced = 0;
                break;
            }
            top--;
            char opening = stack[top];
            if ((ch == ')' && opening != '(') ||
                (ch == ']' && opening != '[') ||
                (ch == '}' && opening != '{')) {
                balanced = 0;
                break;
            }
        }
    }

    if (balanced != 0 && top != 0) {
        balanced = 0;
    }

    free(stack);
    stack = NULL;

    return balanced;
}

int main(void)
{
    const char *tests[] = {
        "{[()]}",
        "{[(])}",
        "(a+b)*(c-d)",
        "((())",
        "a+b*c",
        "())(",
        "}",
        ""
    };

    size_t count = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < count; i++) {
        int result = isBalanced(tests[i]);
        if (result < 0) {
            fprintf(stderr, "Error: failed to evaluate expression\n");
            return EXIT_FAILURE;
        }
        printf("\"%s\" -> %s\n", tests[i], result ? "Balanced" : "Not Balanced");
    }

    return EXIT_SUCCESS;
}