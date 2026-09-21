#include <stdio.h>
#include <stdlib.h>

int is_balanced(const char *expression, size_t length)
{
    char *stack;
    size_t top = 0;

    if (expression == NULL) {
        return -1;
    }

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
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    const char *expression;
    size_t length = 0;
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <expression>\n", argv[0]);
        return EXIT_FAILURE;
    }

    expression = argv[1];

    while (expression[length] != '\0') {
        ++length;
    }

    result = is_balanced(expression, length);
    if (result < 0) {
        fprintf(stderr, "Unable to check the expression\n");
        return EXIT_FAILURE;
    }

    puts(result == 1 ? "Balanced" : "Not balanced");
    return EXIT_SUCCESS;
}