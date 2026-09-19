#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_balanced(const char *expression)
{
    char *stack;
    size_t length;
    size_t top = 0;

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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <expression>\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = is_balanced(argv[1]);
    if (result < 0) {
        fputs("Unable to check the expression\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result == 1 ? "Balanced" : "Not balanced");
    return EXIT_SUCCESS;
}