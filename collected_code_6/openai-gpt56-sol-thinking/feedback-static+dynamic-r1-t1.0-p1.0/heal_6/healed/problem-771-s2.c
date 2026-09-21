#include <stdio.h>
#include <stdlib.h>

#define MAX_EXPRESSION_LENGTH (1024U * 1024U)

typedef enum {
    BALANCE_ERROR = -1,
    NOT_BALANCED = 0,
    BALANCED = 1
} BalanceResult;

static BalanceResult check_balanced(const char *expression, size_t length)
{
    char *stack;
    size_t top = 0;

    if (expression == NULL) {
        return BALANCE_ERROR;
    }

    if (length == 0) {
        return BALANCED;
    }

    stack = malloc(length);
    if (stack == NULL) {
        return BALANCE_ERROR;
    }

    for (size_t i = 0; i < length; ++i) {
        switch (expression[i]) {
        case '(':
        case '[':
        case '{':
            stack[top++] = expression[i];
            break;

        case ')':
            if (top == 0 || stack[top - 1] != '(') {
                free(stack);
                return NOT_BALANCED;
            }
            --top;
            break;

        case ']':
            if (top == 0 || stack[top - 1] != '[') {
                free(stack);
                return NOT_BALANCED;
            }
            --top;
            break;

        case '}':
            if (top == 0 || stack[top - 1] != '{') {
                free(stack);
                return NOT_BALANCED;
            }
            --top;
            break;

        default:
            break;
        }
    }

    free(stack);
    return top == 0 ? BALANCED : NOT_BALANCED;
}

static int read_expression(char **expression, size_t *expression_length)
{
    const size_t maximum_length = (size_t)MAX_EXPRESSION_LENGTH;
    char *buffer;
    size_t length = 0;
    unsigned char character;

    if (expression == NULL || expression_length == NULL) {
        return 0;
    }

    *expression = NULL;
    *expression_length = 0;

    buffer = malloc(maximum_length + 1U);
    if (buffer == NULL) {
        return 0;
    }

    while (fread(&character, sizeof(character), 1U, stdin) == 1U) {
        if (character == (unsigned char)'\n') {
            break;
        }

        if (length >= maximum_length) {
            free(buffer);
            return 0;
        }

        buffer[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *expression = buffer;
    *expression_length = length;

    return 1;
}

int main(void)
{
    char *expression = NULL;
    size_t expression_length = 0;
    BalanceResult result;

    if (!read_expression(&expression, &expression_length)) {
        fputs("Failed to read expression.\n", stderr);
        return EXIT_FAILURE;
    }

    result = check_balanced(expression, expression_length);
    free(expression);

    if (result == BALANCE_ERROR) {
        fputs("Failed to check expression.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result == BALANCED ? "Balanced" : "Not Balanced");
    return EXIT_SUCCESS;
}