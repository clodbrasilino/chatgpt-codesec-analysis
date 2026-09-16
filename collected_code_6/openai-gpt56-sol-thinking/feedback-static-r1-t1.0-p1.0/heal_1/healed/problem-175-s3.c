#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    PARENTHESES_ERROR = -1,
    PARENTHESES_INVALID = 0,
    PARENTHESES_VALID = 1
} ParenthesesResult;

ParenthesesResult verify_parentheses(const char *string)
{
    char *stack;
    size_t length;
    size_t top = 0;

    if (string == NULL) {
        return PARENTHESES_ERROR;
    }

    length = strlen(string);

    if (length == 0) {
        return PARENTHESES_VALID;
    }

    stack = malloc(length * sizeof(*stack));

    if (stack == NULL) {
        return PARENTHESES_ERROR;
    }

    for (size_t i = 0; i < length; ++i) {
        const char current = string[i];

        if (current == '(' || current == '[' || current == '{') {
            stack[top++] = current;
            continue;
        }

        if (current == ')' || current == ']' || current == '}') {
            char opening;

            if (top == 0) {
                free(stack);
                return PARENTHESES_INVALID;
            }

            opening = stack[--top];

            if ((current == ')' && opening != '(') ||
                (current == ']' && opening != '[') ||
                (current == '}' && opening != '{')) {
                free(stack);
                return PARENTHESES_INVALID;
            }

            continue;
        }

        free(stack);
        return PARENTHESES_INVALID;
    }

    free(stack);

    return top == 0 ? PARENTHESES_VALID : PARENTHESES_INVALID;
}

int main(int argc, char * const argv[])
{
    ParenthesesResult result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <parentheses>\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = verify_parentheses(argv[1]);

    if (result == PARENTHESES_ERROR) {
        fputs("Unable to verify the input.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result == PARENTHESES_VALID ? "valid" : "invalid");

    return EXIT_SUCCESS;
}