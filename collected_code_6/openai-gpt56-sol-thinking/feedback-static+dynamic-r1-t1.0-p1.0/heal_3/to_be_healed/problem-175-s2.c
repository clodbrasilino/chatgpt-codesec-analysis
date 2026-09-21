#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    PARENTHESES_ERROR = -1,
    PARENTHESES_INVALID = 0,
    PARENTHESES_VALID = 1
} ParenthesesResult;

ParenthesesResult validate_parentheses(const char *string, size_t length)
{
    char *stack;
    size_t top = 0;

    if (string == NULL) {
        return PARENTHESES_ERROR;
    }

    if (length == 0) {
        return PARENTHESES_VALID;
    }

    if ((length % 2U) != 0U) {
        return PARENTHESES_INVALID;
    }

    stack = malloc(length * sizeof(*stack));
    if (stack == NULL) {
        return PARENTHESES_ERROR;
    }

    for (size_t i = 0; i < length; ++i) {
        const char current = string[i];

        switch (current) {
        case '(':
        case '[':
        case '{':
            if (top >= length) {
                free(stack);
                return PARENTHESES_ERROR;
            }
            stack[top++] = current;
            break;

        case ')':
            if (top == 0 || stack[--top] != '(') {
                free(stack);
                return PARENTHESES_INVALID;
            }
            break;

        case ']':
            if (top == 0 || stack[--top] != '[') {
                free(stack);
                return PARENTHESES_INVALID;
            }
            break;

        case '}':
            if (top == 0 || stack[--top] != '{') {
                free(stack);
                return PARENTHESES_INVALID;
            }
            break;

        default:
            free(stack);
            return PARENTHESES_INVALID;
        }
    }

    free(stack);
    return top == 0 ? PARENTHESES_VALID : PARENTHESES_INVALID;
}

int main(int argc, char **argv)
{
    ParenthesesResult result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <parentheses-string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    result = validate_parentheses(argv[1], strlen(argv[1]));

    if (result == PARENTHESES_ERROR) {
        fputs("Unable to validate the string.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result == PARENTHESES_VALID ? "Valid" : "Invalid");
    return EXIT_SUCCESS;
}