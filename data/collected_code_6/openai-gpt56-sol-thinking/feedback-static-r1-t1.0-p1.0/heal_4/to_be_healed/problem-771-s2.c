#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    BALANCE_ERROR = -1,
    NOT_BALANCED = 0,
    BALANCED = 1
} BalanceResult;

static int ensure_capacity(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || capacity == NULL) {
        return 0;
    }

    if (*buffer == NULL && *capacity != 0) {
        return 0;
    }

    if (required <= *capacity) {
        return 1;
    }

    new_capacity = *capacity == 0 ? 128 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return 0;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 1;
}

static int read_expression(FILE *stream, char **expression,
                           size_t *expression_length)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    if (stream == NULL || expression == NULL || expression_length == NULL) {
        return 0;
    }

    *expression = NULL;
    *expression_length = 0;

    if (!ensure_capacity(&buffer, &capacity, 1)) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF) {
        if (character == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return 0;
        }

        if (!ensure_capacity(&buffer, &capacity, length + 2)) {
            free(buffer);
            return 0;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    if (character == EOF && ferror(stream)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *expression = buffer;
    *expression_length = length;
    return 1;
}

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
        char expected;

        switch (expression[i]) {
            case '(':
            case '[':
            case '{':
                stack[top++] = expression[i];
                continue;

            case ')':
                expected = '(';
                break;

            case ']':
                expected = '[';
                break;

            case '}':
                expected = '{';
                break;

            default:
                continue;
        }

        if (top == 0 || stack[--top] != expected) {
            free(stack);
            return NOT_BALANCED;
        }
    }

    free(stack);
    return top == 0 ? BALANCED : NOT_BALANCED;
}

int main(void)
{
    char *expression = NULL;
    size_t expression_length = 0;
    BalanceResult result;

    if (!read_expression(stdin, &expression, &expression_length)) {
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