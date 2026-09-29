#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_balanced(const char *expression)
{
    size_t length;
    size_t top = 0;
    char *stack;

    if (expression == NULL) {
        return -1;
    }

    length = strlen(expression);

    if (length == 0) {
        return 1;
    }

    stack = malloc(length * sizeof(*stack));
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

int main(int argc, char *const argv[])
{
    int result;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <expression>\n", program_name);
        return EXIT_FAILURE;
    }

    result = is_balanced(argv[1]);

    if (result < 0) {
        fprintf(stderr, "Unable to check the expression\n");
        return EXIT_FAILURE;
    }

    puts(result == 1 ? "Balanced" : "Not balanced");
    return EXIT_SUCCESS;
}