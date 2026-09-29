#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    BALANCE_ERROR = -1,
    BALANCE_UNBALANCED = 0,
    BALANCE_BALANCED = 1
} BalanceResult;

static BalanceResult check_balanced(const char *expression)
{
    unsigned char *stack;
    size_t length;
    size_t top = 0;
    BalanceResult result = BALANCE_BALANCED;

    if (expression == NULL) {
        return BALANCE_ERROR;
    }

    length = strlen(expression);

    if (length == 0) {
        return BALANCE_BALANCED;
    }

    stack = malloc(length * sizeof(*stack));
    if (stack == NULL) {
        return BALANCE_ERROR;
    }

    for (size_t i = 0; i < length; ++i) {
        const unsigned char current = (unsigned char)expression[i];

        if (current == '(' || current == '[' || current == '{') {
            if (top >= length) {
                result = BALANCE_ERROR;
                break;
            }

            stack[top++] = current;
        } else if (current == ')' || current == ']' || current == '}') {
            unsigned char opening;

            if (top == 0) {
                result = BALANCE_UNBALANCED;
                break;
            }

            opening = stack[--top];

            if ((current == ')' && opening != '(') ||
                (current == ']' && opening != '[') ||
                (current == '}' && opening != '{')) {
                result = BALANCE_UNBALANCED;
                break;
            }
        }
    }

    if (result == BALANCE_BALANCED && top != 0) {
        result = BALANCE_UNBALANCED;
    }

    free(stack);
    return result;
}

int main(int argc, char **const argv)
{
    const char *program_name = "program";
    BalanceResult result;

    if (argv != NULL && argc > 0 && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"expression\"\n", program_name);
        return EXIT_FAILURE;
    }

    result = check_balanced(argv[1]);

    if (result == BALANCE_ERROR) {
        fputs("Unable to check the expression.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result == BALANCE_BALANCED ? "Balanced" : "Not balanced");
    return EXIT_SUCCESS;
}