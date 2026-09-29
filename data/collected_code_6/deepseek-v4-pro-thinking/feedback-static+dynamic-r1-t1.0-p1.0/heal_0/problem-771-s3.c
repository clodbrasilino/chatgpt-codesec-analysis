#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    CHECK_ERROR = -1,
    CHECK_UNBALANCED = 0,
    CHECK_BALANCED = 1
};

static int is_matching_pair(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

int is_balanced(const char *expr)
{
    if (expr == NULL) {
        return CHECK_ERROR;
    }

    size_t len = strlen(expr);
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

            char open = stack[--top];
            if (!is_matching_pair(open, c)) {
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
    int status = is_balanced(expr);

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