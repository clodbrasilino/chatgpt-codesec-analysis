#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_balanced(const char *expression, size_t length)
{
    char *stack;
    size_t top = 0;

    if (expression == NULL) {
        return -1;
    }

    if (length == 0) {
        return 1;
    }

    stack = malloc(length);
    if (stack == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        char current = expression[i];

        switch (current) {
        case '(':
        case '[':
        case '{':
            stack[top++] = current;
            break;

        case ')':
        case ']':
        case '}':
            if (top == 0) {
                free(stack);
                return 0;
            }

            --top;

            if ((current == ')' && stack[top] != '(') ||
                (current == ']' && stack[top] != '[') ||
                (current == '}' && stack[top] != '{')) {
                free(stack);
                return 0;
            }
            break;

        default:
            break;
        }
    }

    free(stack);
    return top == 0;
}

int main(int argc, char **argv)
{
    const char *expression;
    size_t length;
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <expression>\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    expression = argv[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(expression);

    result = is_balanced(expression, length);
    if (result < 0) {
        fputs("Unable to check the expression\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result ? "Balanced" : "Not balanced");
    return EXIT_SUCCESS;
}