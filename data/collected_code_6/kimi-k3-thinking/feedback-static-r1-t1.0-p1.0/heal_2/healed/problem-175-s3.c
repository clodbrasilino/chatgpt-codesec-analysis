#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 4096

static bool is_open_bracket(char c)
{
    return c == '(' || c == '[' || c == '{';
}

static bool is_close_bracket(char c)
{
    return c == ')' || c == ']' || c == '}';
}

static bool is_matching(char left, char right)
{
    return (left == '(' && right == ')') ||
           (left == '[' && right == ']') ||
           (left == '{' && right == '}');
}

static size_t bounded_length(const char *s, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && s[len] != '\0')
    {
        len++;
    }

    return len;
}

bool is_valid_parentheses(const char *s)
{
    if (s == NULL)
    {
        return false;
    }

    size_t len = bounded_length(s, MAX_INPUT_LENGTH);
    size_t capacity = (len == 0) ? 1 : len;
    char *stack = malloc(capacity * sizeof(*stack));
    if (stack == NULL)
    {
        return false;
    }

    size_t top = 0;
    bool valid = true;

    for (size_t i = 0; i < len; i++)
    {
        char c = s[i];
        if (is_open_bracket(c))
        {
            stack[top] = c;
            top++;
        }
        else if (is_close_bracket(c))
        {
            if (top == 0 || !is_matching(stack[top - 1], c))
            {
                valid = false;
                break;
            }
            top--;
        }
    }

    if (top != 0)
    {
        valid = false;
    }

    free(stack);
    return valid;
}

int main(void)
{
    const char *tests[] = {
        "()",
        "()[]{}",
        "(]",
        "([)]",
        "{[]}",
        "",
        "(",
        ")))",
        "((()))"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < count; i++)
    {
        printf("\"%s\" -> %s\n", tests[i],
               is_valid_parentheses(tests[i]) ? "valid" : "invalid");
    }

    return 0;
}