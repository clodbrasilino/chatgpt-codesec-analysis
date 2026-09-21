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
        char expected;

        switch (current) {
            case '(':
            case '[':
            case '{':
                stack[top++] = current;
                break;

            case ')':
                expected = '(';
                goto check_closing;

            case ']':
                expected = '[';
                goto check_closing;

            case '}':
                expected = '{';

check_closing:
                if (top == 0 || stack[--top] != expected) {
                    free(stack);
                    return NOT_BALANCED;
                }
                break;

            default:
                break;
        }
    }

    free(stack);
    return top == 0 ? BALANCED : NOT_BALANCED;
}

static int grow_buffer(char **buffer, size_t *capacity)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || *buffer == NULL || capacity == NULL) {
        return 0;
    }

    if (*capacity > SIZE_MAX / 2) {
        return 0;
    }

    new_capacity = *capacity * 2;
    resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return 0;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 1;
}

static int read_expression(char **expression, size_t *expression_length)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;
    int character = 0;

    if (expression == NULL || expression_length == NULL) {
        return 0;
    }

    *expression = NULL;
    *expression_length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == capacity - 1) {
            if (!grow_buffer(&buffer, &capacity)) {
                free(buffer);
                return 0;
            }
        }

        buffer[length++] = (char)(unsigned char)character;
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