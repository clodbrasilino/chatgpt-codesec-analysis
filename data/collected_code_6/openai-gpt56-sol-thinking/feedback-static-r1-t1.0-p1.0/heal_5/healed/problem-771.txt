#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    BALANCE_ERROR = -1,
    BALANCE_UNBALANCED = 0,
    BALANCE_BALANCED = 1
} BalanceResult;

typedef enum {
    OPEN_PARENTHESIS,
    OPEN_BRACKET,
    OPEN_BRACE
} OpeningDelimiter;

static BalanceResult check_balanced(const char *expression, size_t length)
{
    OpeningDelimiter *stack;
    size_t top = 0;
    BalanceResult result = BALANCE_BALANCED;

    if (expression == NULL) {
        return BALANCE_ERROR;
    }

    if (length == 0) {
        return BALANCE_BALANCED;
    }

    if (length > SIZE_MAX / sizeof(*stack)) {
        return BALANCE_ERROR;
    }

    stack = malloc(length * sizeof(*stack));
    if (stack == NULL) {
        return BALANCE_ERROR;
    }

    for (size_t i = 0; i < length; ++i) {
        switch (expression[i]) {
        case '(':
            stack[top++] = OPEN_PARENTHESIS;
            break;

        case '[':
            stack[top++] = OPEN_BRACKET;
            break;

        case '{':
            stack[top++] = OPEN_BRACE;
            break;

        case ')':
            if (top == 0 || stack[--top] != OPEN_PARENTHESIS) {
                result = BALANCE_UNBALANCED;
            }
            break;

        case ']':
            if (top == 0 || stack[--top] != OPEN_BRACKET) {
                result = BALANCE_UNBALANCED;
            }
            break;

        case '}':
            if (top == 0 || stack[--top] != OPEN_BRACE) {
                result = BALANCE_UNBALANCED;
            }
            break;

        default:
            break;
        }

        if (result == BALANCE_UNBALANCED) {
            break;
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
    const char *expression;
    BalanceResult result;

    if (argv != NULL && argc > 0 && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"expression\"\n", program_name);
        return EXIT_FAILURE;
    }

    expression = argv[1];
    result = check_balanced(expression, strlen(expression));

    if (result == BALANCE_ERROR) {
        fputs("Unable to check the expression.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result == BALANCE_BALANCED ? "Balanced" : "Not balanced");
    return EXIT_SUCCESS;
}