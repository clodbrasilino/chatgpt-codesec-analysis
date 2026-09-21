#include <stdio.h>
#include <stdlib.h>

typedef enum {
    PARENTHESES_ERROR = -1,
    PARENTHESES_INVALID = 0,
    PARENTHESES_VALID = 1
} ParenthesesResult;

ParenthesesResult verify_parentheses(const char *string, size_t length)
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

        if (current == '(' || current == '[' || current == '{') {
            stack[top++] = current;
        } else if (current == ')' || current == ']' || current == '}') {
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
        } else {
            free(stack);
            return PARENTHESES_INVALID;
        }
    }

    free(stack);
    return top == 0 ? PARENTHESES_VALID : PARENTHESES_INVALID;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    const char *input;
    size_t input_length = 0;
    ParenthesesResult result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <parentheses>\n",
                argc > 0 ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    input = argv[1];

    while (input[input_length] != '\0') {
        ++input_length;
    }

    result = verify_parentheses(input, input_length);

    if (result == PARENTHESES_ERROR) {
        fputs("Unable to verify the input.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result == PARENTHESES_VALID ? "valid" : "invalid");
    return EXIT_SUCCESS;
}