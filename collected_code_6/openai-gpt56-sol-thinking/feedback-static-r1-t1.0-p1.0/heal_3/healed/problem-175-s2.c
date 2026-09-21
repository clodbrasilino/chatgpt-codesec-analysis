#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    PARENTHESES_ERROR = -1,
    PARENTHESES_INVALID = 0,
    PARENTHESES_VALID = 1
} ParenthesesResult;

static ParenthesesResult validate_parentheses(const char *string)
{
    char *stack = NULL;
    size_t top = 0;
    size_t capacity = 0;

    if (string == NULL) {
        return PARENTHESES_ERROR;
    }

    for (const char *current = string; *current != '\0'; ++current) {
        char expected;

        switch (*current) {
        case '(':
            expected = ')';
            break;
        case '[':
            expected = ']';
            break;
        case '{':
            expected = '}';
            break;
        case ')':
        case ']':
        case '}':
            if (top == 0 || stack[--top] != *current) {
                free(stack);
                return PARENTHESES_INVALID;
            }
            continue;
        default:
            free(stack);
            return PARENTHESES_INVALID;
        }

        if (top == capacity) {
            size_t new_capacity;
            char *new_stack;

            if (capacity == SIZE_MAX) {
                free(stack);
                return PARENTHESES_ERROR;
            }

            if (capacity == 0) {
                new_capacity = 16;
            } else if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            new_stack = realloc(stack, new_capacity);
            if (new_stack == NULL) {
                free(stack);
                return PARENTHESES_ERROR;
            }

            stack = new_stack;
            capacity = new_capacity;
        }

        stack[top++] = expected;
    }

    free(stack);
    return top == 0 ? PARENTHESES_VALID : PARENTHESES_INVALID;
}

int main(int argc, char *argv[const])
{
    ParenthesesResult result;

    if (argc != 2) {
        fputs("Usage: program <parentheses-string>\n", stderr);
        return EXIT_FAILURE;
    }

    result = validate_parentheses(argv[1]);

    if (result == PARENTHESES_ERROR) {
        fputs("Unable to validate the string.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result == PARENTHESES_VALID ? "Valid" : "Invalid");
    return EXIT_SUCCESS;
}