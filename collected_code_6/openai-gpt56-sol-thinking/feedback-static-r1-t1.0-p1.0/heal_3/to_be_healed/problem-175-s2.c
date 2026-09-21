#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    PARENTHESES_ERROR = -1,
    PARENTHESES_INVALID = 0,
    PARENTHESES_VALID = 1
} ParenthesesResult;

static ParenthesesResult validate_parentheses(const char *string, size_t length)
{
    char *stack;
    size_t top = 0;

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
        switch (string[i]) {
        case '(':
            stack[top++] = ')';
            break;
        case '[':
            stack[top++] = ']';
            break;
        case '{':
            stack[top++] = '}';
            break;
        case ')':
        case ']':
        case '}':
            if (top == 0 || stack[--top] != string[i]) {
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    ParenthesesResult result;

    if (argc != 2) {
        fputs("Usage: program <parentheses-string>\n", stderr);
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