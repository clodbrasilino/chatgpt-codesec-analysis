#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define INITIAL_CAPACITY 128U
#define INPUT_CHUNK_SIZE 4096U
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

            if (stack[--top] != expected) {
                free(stack);
                return NOT_BALANCED;
            }
        }
    }

    free(stack);
    return top == 0 ? BALANCED : NOT_BALANCED;
}

static int append_character(char **buffer, size_t *length,
                            size_t *capacity, unsigned char character)
{
    size_t required_capacity;

    if (buffer == NULL || length == NULL || capacity == NULL ||
        *buffer == NULL || *capacity == 0 || *length >= *capacity ||
        *length > SIZE_MAX - 2U) {
        return 0;
    }

    required_capacity = *length + 2U;

    if (required_capacity > *capacity) {
        size_t new_capacity = *capacity;
        char *resized;

        while (new_capacity < required_capacity) {
            if (new_capacity > SIZE_MAX / 2U) {
                new_capacity = required_capacity;
                break;
            }

            new_capacity *= 2U;
        }

        resized = realloc(*buffer, new_capacity);
        if (resized == NULL) {
            return 0;
        }

        *buffer = resized;
        *capacity = new_capacity;
    }

    (*buffer)[*length] = (char)character;
    ++(*length);
    (*buffer)[*length] = '\0';

    return 1;
}

static int read_expression(char **expression, size_t *expression_length)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[INPUT_CHUNK_SIZE];
    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0;
    char *buffer;

    if (expression == NULL || expression_length == NULL) {
        return 0;
    }

    *expression = NULL;
    *expression_length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    buffer[0] = '\0';

    for (;;) {
        size_t bytes_read = fread(input, 1U, sizeof(input), stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (input[i] == '\n') {
                *expression = buffer;
                *expression_length = length;
                return 1;
            }

            if (length == MAX_EXPRESSION_LENGTH ||
                !append_character(&buffer, &length, &capacity, input[i])) {
                free(buffer);
                return 0;
            }
        }

        if (bytes_read < sizeof(input)) {
            if (ferror(stdin)) {
                free(buffer);
                return 0;
            }

            if (feof(stdin)) {
                *expression = buffer;
                *expression_length = length;
                return 1;
            }
        }
    }
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