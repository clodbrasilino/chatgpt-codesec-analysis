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
    if (expression == NULL) {
        return BALANCE_ERROR;
    }

    const size_t length = strlen(expression);

    if (length == 0) {
        return BALANCE_BALANCED;
    }

    char *stack = malloc(length * sizeof(*stack));
    if (stack == NULL) {
        return BALANCE_ERROR;
    }

    size_t top = 0;
    BalanceResult result = BALANCE_BALANCED;

    for (size_t i = 0; i < length; ++i) {
        const char current = expression[i];

        if (current == '(' || current == '[' || current == '{') {
            stack[top++] = current;
            continue;
        }

        if (current == ')' || current == ']' || current == '}') {
            if (top == 0) {
                result = BALANCE_UNBALANCED;
                break;
            }

            const char opening = stack[--top];

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

int main(int argc, char *argv[const])
{
    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s \"expression\"\n", program_name);
        return EXIT_FAILURE;
    }

    const BalanceResult result = check_balanced(argv[1]);

    if (result == BALANCE_ERROR) {
        fputs("Unable to check the expression.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result == BALANCE_BALANCED ? "Balanced" : "Not balanced");
    return EXIT_SUCCESS;
}