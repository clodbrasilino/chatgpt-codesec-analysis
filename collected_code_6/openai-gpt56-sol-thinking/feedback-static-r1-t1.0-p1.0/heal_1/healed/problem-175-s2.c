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

    stack = malloc(length);
    if (stack == NULL) {
        return PARENTHESES_ERROR;
    }

    for (size_t i = 0; i < length; ++i) {
        const char current = string[i];

        switch (current) {
        case '(':
        case '[':
        case '{':
            stack[top++] = current;
            break;

        case ')':
        case ']':
        case '}':
            if (top == 0) {
                free(stack);
                return PARENTHESES_INVALID;
            }

            --top;

            if ((current == ')' && stack[top] != '(') ||
                (current == ']' && stack[top] != '[') ||
                (current == '}' && stack[top] != '{')) {
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

int main(int argc, char *argv[const])
{
    ParenthesesResult result;
    size_t length = 0;

    if (argc != 2) {
        fputs("Usage: program <parentheses-string>\n", stderr);
        return EXIT_FAILURE;
    }

    while (argv[1][length] != '\0') {
        ++length;
    }

    result = validate_parentheses(argv[1], length);

    if (result == PARENTHESES_ERROR) {
        fputs("Unable to validate the string.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result == PARENTHESES_VALID ? "Valid" : "Invalid");
    return EXIT_SUCCESS;
}