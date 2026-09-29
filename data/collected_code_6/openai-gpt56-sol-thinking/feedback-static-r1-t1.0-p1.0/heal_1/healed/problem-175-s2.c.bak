#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    PARENTHESES_ERROR = -1,
    PARENTHESES_INVALID = 0,
    PARENTHESES_VALID = 1
} ParenthesesResult;

ParenthesesResult validate_parentheses(const char *string)
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

    stack = malloc(length * sizeof *stack);
    if (stack == NULL) {
        return PARENTHESES_ERROR;
    }

    for (size_t i = 0; i < length; ++i) {
        const char current = string[i];

        if (current == '(' || current == '[' || current == '{') {
            stack[top++] = current;
            continue;
        }

        if (current != ')' && current != ']' && current != '}') {
            free(stack);
            return PARENTHESES_INVALID;
        }

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
    }

    free(stack);

    return top == 0 ? PARENTHESES_VALID : PARENTHESES_INVALID;
}

int main(int argc, char *const argv[])
{
    ParenthesesResult result;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <parentheses-string>\n", program_name);
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