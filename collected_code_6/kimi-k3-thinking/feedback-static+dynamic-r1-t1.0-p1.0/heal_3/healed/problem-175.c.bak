#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_valid_parentheses(const char *str)
{
    if (str == NULL)
    {
        return false;
    }

    char *stack = malloc(strlen(str) + 1);

    if (stack == NULL)
    {
        return false;
    }

    bool valid = true;
    size_t top = 0;

    for (const char *p = str; *p != '\0'; ++p)
    {
        const char c = *p;

        if (c == '(' || c == '[' || c == '{')
        {
            stack[top++] = c;
        }
        else if (c == ')' || c == ']' || c == '}')
        {
            const char expected = (c == ')') ? '(' : (c == ']') ? '[' : '{';

            if (top == 0 || stack[--top] != expected)
            {
                valid = false;
                break;
            }
        }
        else
        {
            valid = false;
            break;
        }
    }

    if (top != 0)
    {
        valid = false;
    }

    free(stack);

    return valid;
}

int main(int argc, const char *argv[])
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            printf("%s\n", is_valid_parentheses(argv[i]) ? "True" : "False");
        }
    }
    else
    {
        char buffer[65536];

        while (fgets(buffer, sizeof buffer, stdin) != NULL)
        {
            buffer[strcspn(buffer, "\r\n")] = '\0';
            printf("%s\n", is_valid_parentheses(buffer) ? "True" : "False");
        }
    }

    return EXIT_SUCCESS;
}