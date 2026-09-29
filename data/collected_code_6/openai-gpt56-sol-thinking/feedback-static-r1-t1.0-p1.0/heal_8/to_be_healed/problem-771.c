#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

static int push_delimiter(OpeningDelimiter **stack, size_t *top,
                          size_t *capacity, OpeningDelimiter delimiter)
{
    if (*top == *capacity) {
        size_t new_capacity;
        OpeningDelimiter *new_stack;

        if (*capacity == 0) {
            new_capacity = 16;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                return 0;
            }
            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof **stack) {
            return 0;
        }

        new_stack = realloc(*stack, new_capacity * sizeof **stack);
        if (new_stack == NULL) {
            return 0;
        }

        *stack = new_stack;
        *capacity = new_capacity;
    }

    (*stack)[(*top)++] = delimiter;
    return 1;
}

static BalanceResult check_balanced(const char *expression)
{
    OpeningDelimiter *stack = NULL;
    size_t top = 0;
    size_t capacity = 0;
    BalanceResult result = BALANCE_BALANCED;
    const unsigned char *current;

    if (expression == NULL) {
        return BALANCE_ERROR;
    }

    current = (const unsigned char *)expression;

    while (*current != '\0') {
        switch (*current) {
        case '(':
            if (!push_delimiter(&stack, &top, &capacity, OPEN_PARENTHESIS)) {
                result = BALANCE_ERROR;
            }
            break;

        case '[':
            if (!push_delimiter(&stack, &top, &capacity, OPEN_BRACKET)) {
                result = BALANCE_ERROR;
            }
            break;

        case '{':
            if (!push_delimiter(&stack, &top, &capacity, OPEN_BRACE)) {
                result = BALANCE_ERROR;
            }
            break;

        case ')':
            if (top == 0 || stack[top - 1] != OPEN_PARENTHESIS) {
                result = BALANCE_UNBALANCED;
            } else {
                --top;
            }
            break;

        case ']':
            if (top == 0 || stack[top - 1] != OPEN_BRACKET) {
                result = BALANCE_UNBALANCED;
            } else {
                --top;
            }
            break;

        case '}':
            if (top == 0 || stack[top - 1] != OPEN_BRACE) {
                result = BALANCE_UNBALANCED;
            } else {
                --top;
            }
            break;

        default:
            break;
        }

        if (result != BALANCE_BALANCED) {
            break;
        }

        ++current;
    }

    if (result == BALANCE_BALANCED && top != 0) {
        result = BALANCE_UNBALANCED;
    }

    free(stack);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
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