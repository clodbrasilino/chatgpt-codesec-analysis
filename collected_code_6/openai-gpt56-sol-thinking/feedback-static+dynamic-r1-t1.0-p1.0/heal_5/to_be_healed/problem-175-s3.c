#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    PARENTHESES_ERROR = -1,
    PARENTHESES_INVALID = 0,
    PARENTHESES_VALID = 1
} ParenthesesResult;

ParenthesesResult verify_parentheses(const char *string)
{
    char *stack = NULL;
    size_t capacity = 0;
    size_t top = 0;
    ParenthesesResult result = PARENTHESES_VALID;

    if (string == NULL) {
        return PARENTHESES_ERROR;
    }

    for (const char *p = string; *p != '\0'; ++p) {
        const char current = *p;

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
                    if (capacity > SIZE_MAX / 2) {
                        result = PARENTHESES_ERROR;
                        goto cleanup;
                    }

                    new_capacity = capacity * 2;
                }

                new_stack = realloc(stack, new_capacity);
                if (new_stack == NULL) {
                    result = PARENTHESES_ERROR;
                    goto cleanup;
                }

                stack = new_stack;
                capacity = new_capacity;
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[])
{
    ParenthesesResult result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <parentheses>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
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