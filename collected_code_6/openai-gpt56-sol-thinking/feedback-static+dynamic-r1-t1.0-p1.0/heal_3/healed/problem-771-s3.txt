#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int is_balanced(const char *expression)
{
    char *stack = NULL;
    size_t capacity = 0;
    size_t top = 0;

    if (expression == NULL) {
        return -1;
    }

    for (size_t i = 0; expression[i] != '\0'; ++i) {
        char current = expression[i];

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
                        free(stack);
                        return -1;
                    }
                    new_capacity = capacity * 2;
                }

                new_stack = realloc(stack, new_capacity);
                if (new_stack == NULL) {
                    free(stack);
                    return -1;
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
                free(stack);
                return 0;
            }

            --top;

            if ((current == ')' && stack[top] != '(') ||
                (current == ']' && stack[top] != '[') ||
                (current == '}' && stack[top] != '{')) {
                free(stack);
                return 0;
            }
            break;

        default:
            break;
        }
    }

    free(stack);
    return top == 0;
}

int main(int argc, char **argv)
{
    int result;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <expression>\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    result = is_balanced(argv[1]);
    if (result < 0) {
        fputs("Unable to check the expression\n", stderr);
        return EXIT_FAILURE;
    }

    puts(result ? "Balanced" : "Not balanced");
    return EXIT_SUCCESS;
}