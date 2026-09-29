#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    BALANCE_ERROR = -1,
    BALANCE_UNBALANCED = 0,
    BALANCE_BALANCED = 1
} BalanceResult;

static size_t get_string_length(const char *string)
{
    size_t length = 0;

    while (string[length] != '\0') {
        ++length;
    }

    return length;
}

static BalanceResult check_balanced(const char *expression, size_t length)
{
    char *stack;
    size_t top = 0;
    BalanceResult result = BALANCE_BALANCED;

    if (expression == NULL) {
        return BALANCE_ERROR;
    }

    if (length == 0) {
        return BALANCE_BALANCED;
    }

    stack = malloc(length * sizeof(*stack));
    if (stack == NULL) {
        return BALANCE_ERROR;
    }

    for (size_t i = 0; i < length; ++i) {
        const char current = expression[i];

        if (current == '(' || current == '[' || current == '{') {
            stack[top++] = current;
        } else if (current == ')' || current == ']' || current == '}') {
            char opening;

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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    const char *program_name = "program";
    size_t expression_length;
    BalanceResult result;

    if (argv != NULL && argc > 0 && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"expression\"\n", program_name);
        return EXIT_FAILURE;
    }

    expression_length = get_string_length(argv[1]);
    result = check_balanced(argv[1], expression_length);

    if (result == BALANCE_ERROR) {
        fputs("Unable to check the expression.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result == BALANCE_BALANCED ? "Balanced" : "Not balanced");

    return EXIT_SUCCESS;
}