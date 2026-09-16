#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef enum {
    BALANCE_ERROR = -1,
    NOT_BALANCED = 0,
    BALANCED = 1
} BalanceResult;

static BalanceResult check_balanced(const char *expression)
{
    char *stack;
    size_t length;
    size_t top = 0;

    if (expression == NULL) {
        return BALANCE_ERROR;
    }

    length = strlen(expression);

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

            expected = current == ')' ? '(' : current == ']' ? '[' : '{';

            if (stack[--top] != expected) {
                free(stack);
                return NOT_BALANCED;
            }
        }
    }

    free(stack);
    return top == 0 ? BALANCED : NOT_BALANCED;
}

static int read_expression(char **expression)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;
    int character;

    if (expression == NULL) {
        return 0;
    }

    *expression = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        char *resized;

        if (character == '\0') {
            free(buffer);
            return 0;
        }

        if (length == capacity - 1) {
            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return 0;
            }

            capacity *= 2U;
            resized = realloc(buffer, capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
        }

        buffer[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *expression = buffer;
    return 1;
}

int main(void)
{
    char *expression;
    BalanceResult result;

    if (!read_expression(&expression)) {
        fputs("Failed to read expression.\n", stderr);
        return EXIT_FAILURE;
    }

    result = check_balanced(expression);
    free(expression);

    if (result == BALANCE_ERROR) {
        fputs("Failed to check expression.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result == BALANCED ? "Balanced" : "Not Balanced");
    return EXIT_SUCCESS;
}