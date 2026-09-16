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
    char *stack;
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

    stack = malloc(length);
    if (stack == NULL) {
        return BALANCE_ERROR;
    }

    for (size_t i = 0; i < length; ++i) {
        char current = expression[i];

        if (current == '(' || current == '[' || current == '{') {
            stack[top++] = current;
        } else if (current == ')' || current == ']' || current == '}') {
            if (top == 0) {
                result = BALANCE_UNBALANCED;
                break;
            }

            char opening = stack[--top];

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

int main(int argc, char *argv[])
{
    BalanceResult result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"expression\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = check_balanced(argv[1]);

    if (result == BALANCE_ERROR) {
        fprintf(stderr, "Unable to check the expression.\n");
        return EXIT_FAILURE;
    }

    if (result == BALANCE_BALANCED) {
        puts("Balanced");
    } else {
        puts("Not balanced");
    }

    return EXIT_SUCCESS;
}