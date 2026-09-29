#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static size_t argument_length(const char *argument)
{
    const char *end = argument;

    while (*end != '\0') {
        ++end;
    }

    return (size_t)(end - argument);
}

static int is_balanced(const char *expression, size_t length)
{
    char *stack;
    size_t top = 0;

    if (expression == NULL) {
        return -1;
    }

    if (length == 0) {
        return 1;
    }

    stack = malloc(length);
    if (stack == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        const char current = expression[i];

        if (current == '(' || current == '[' || current == '{') {
            stack[top++] = current;
        } else if (current == ')' || current == ']' || current == '}') {
            char opening;

            if (top == 0) {
                free(stack);
                return 0;
            }

            opening = stack[--top];

            if ((current == ')' && opening != '(') ||
                (current == ']' && opening != '[') ||
                (current == '}' && opening != '{')) {
                free(stack);
                return 0;
            }
        }
    }

    free(stack);
    return top == 0 ? 1 : 0;
}

int main(int argc, char * const argv[])
{
    const char *expression;
    size_t length;
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <expression>\n", argv[0]);
        return EXIT_FAILURE;
    }

    expression = argv[1];
    length = argument_length(expression);
    result = is_balanced(expression, length);

    if (result < 0) {
        fprintf(stderr, "Unable to check the expression\n");
        return EXIT_FAILURE;
    }

    puts(result == 1 ? "Balanced" : "Not balanced");
    return EXIT_SUCCESS;
}