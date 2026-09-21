#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    CHECK_ERROR = -1,
    CHECK_UNBALANCED = 0,
    CHECK_BALANCED = 1
};

static int is_matching_pair(char opening, char closing)
{
    return (opening == '(' && closing == ')') ||
           (opening == '{' && closing == '}') ||
           (opening == '[' && closing == ']');
}

int is_balanced(const char *expr, size_t len)
{
    if (expr == NULL) {
        return CHECK_ERROR;
    }

    char *stack = malloc(len + 1);
    if (stack == NULL) {
        return CHECK_ERROR;
    }

    size_t top = 0;

    for (size_t i = 0; i < len; ++i) {
        char c = expr[i];

        if (c == '(' || c == '{' || c == '[') {
            stack[top++] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == 0) {
                free(stack);
                return CHECK_UNBALANCED;
            }

            char opening_brace = stack[--top];
            if (!is_matching_pair(opening_brace, c)) {
                free(stack);
                return CHECK_UNBALANCED;
            }
        }
    }

    int status = (top == 0) ? CHECK_BALANCED : CHECK_UNBALANCED;
    free(stack);
    return status;
}

int main(void)
{
    const char *expr = "{[()]}";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int status = is_balanced(expr, strlen(expr));

    if (status == CHECK_ERROR) {
        fprintf(stderr, "Error: invalid input or allocation failure\n");
        return EXIT_FAILURE;
    }

    if (status == CHECK_BALANCED) {
        puts("Balanced");
    } else {
        puts("Not balanced");
    }

    return EXIT_SUCCESS;
}