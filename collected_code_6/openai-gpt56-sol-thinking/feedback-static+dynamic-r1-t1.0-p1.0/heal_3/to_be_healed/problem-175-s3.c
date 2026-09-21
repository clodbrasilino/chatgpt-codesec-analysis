#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    PARENTHESES_ERROR = -1,
    PARENTHESES_INVALID = 0,
    PARENTHESES_VALID = 1
} ParenthesesResult;

ParenthesesResult verify_parentheses(const char *string, size_t length)
{
    char *stack;
    size_t top = 0;
    ParenthesesResult result = PARENTHESES_VALID;

    if (string == NULL) {
        return PARENTHESES_ERROR;
    }

    if (length == 0) {
        return PARENTHESES_VALID;
    }

    stack = malloc(length * sizeof(*stack));
    if (stack == NULL) {
        return PARENTHESES_ERROR;
    }

    for (size_t i = 0; i < length; ++i) {
        char current = string[i];

        switch (current) {
        case '(':
        case '[':
        case '{':
            if (top >= length) {
                result = PARENTHESES_ERROR;
                goto cleanup;
            }
            stack[top++] = current;
            break;

        case ')':
        case ']':
        case '}':
            if (top == 0) {
                result = PARENTHESES_INVALID;
                goto cleanup;
            }

            --top;

            if ((current == ')' && stack[top] != '(') ||
                (current == ']' && stack[top] != '[') ||
                (current == '}' && stack[top] != '{')) {
                result = PARENTHESES_INVALID;
                goto cleanup;
            }
            break;

        default:
            result = PARENTHESES_INVALID;
            goto cleanup;
        }
    }

    if (top != 0) {
        result = PARENTHESES_INVALID;
    }

cleanup:
    free(stack);
    return result;
}

int main(int argc, char **argv)
{
    const char *input;
    size_t input_length;
    ParenthesesResult result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <parentheses>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    input = argv[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);
    result = verify_parentheses(input, input_length);

    if (result == PARENTHESES_ERROR) {
        fputs("Unable to verify the input.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result == PARENTHESES_VALID ? "valid" : "invalid");
    return EXIT_SUCCESS;
}