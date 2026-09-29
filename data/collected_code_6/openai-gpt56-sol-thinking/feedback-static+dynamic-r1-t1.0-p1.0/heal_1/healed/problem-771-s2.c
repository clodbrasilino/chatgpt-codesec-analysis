#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
        char current = expression[i];

        if (current == '(' || current == '[' || current == '{') {
            stack[top++] = current;
        } else if (current == ')' || current == ']' || current == '}') {
            char expected;

            if (top == 0) {
                free(stack);
                return NOT_BALANCED;
            }

            if (current == ')') {
                expected = '(';
            } else if (current == ']') {
                expected = '[';
            } else {
                expected = '{';
            }

            --top;
            if (stack[top] != expected) {
                free(stack);
                return NOT_BALANCED;
            }
        }
    }

    free(stack);
    return top == 0 ? BALANCED : NOT_BALANCED;
}

static int read_expression(char **expression, size_t *expression_length)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;
    int character;

    if (expression == NULL || expression_length == NULL) {
        return 0;
    }

    *expression = NULL;
    *expression_length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        character = fgetc(stdin);

        if (character == '\n' || character == EOF) {
            break;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2U;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
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
    char *expression;
    size_t expression_length;
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