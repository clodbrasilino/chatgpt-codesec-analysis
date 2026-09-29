#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    PARENTHESES_ERROR = -1,
    PARENTHESES_INVALID = 0,
    PARENTHESES_VALID = 1
} ParenthesesResult;

ParenthesesResult validate_parentheses(const char *string)
{
    char *stack = NULL;
    size_t capacity = 0;
    size_t top = 0;

    if (string == NULL) {
        return PARENTHESES_ERROR;
    }

    for (size_t i = 0; string[i] != '\0'; ++i) {
        char expected;
        char current = string[i];

        switch (current) {
        case '(':
        case '[':
        case '{':
            if (top == capacity) {
                size_t new_capacity;
                char *new_stack;

                if (capacity == 0) {
                    new_capacity = 16;
                } else {
                    if (capacity > (size_t)-1 / 2) {
                        free(stack);
                        return PARENTHESES_ERROR;
                    }
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

            stack[top++] = current;
            break;

        case ')':
            expected = '(';
            goto check_closing;

        case ']':
            expected = '[';
            goto check_closing;

        case '}':
            expected = '{';

        check_closing:
            if (top == 0 || stack[top - 1] != expected) {
                free(stack);
                return PARENTHESES_INVALID;
            }
            --top;
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

    result = validate_parentheses(argv[1]);

    if (result == PARENTHESES_ERROR) {
        fputs("Unable to validate the string.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result == PARENTHESES_VALID ? "Valid" : "Invalid");
    return EXIT_SUCCESS;
}