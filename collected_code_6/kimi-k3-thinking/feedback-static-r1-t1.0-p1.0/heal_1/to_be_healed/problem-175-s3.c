#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool is_opening(char c)
{
    return c == '(' || c == '[' || c == '{';
}

static bool is_closing(char c)
{
    return c == ')' || c == ']' || c == '}';
}

/* Possible weaknesses found:
 * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
 */
static bool is_matching(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

bool is_valid_parentheses(const char *s)
{
    if (s == NULL)
    {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s);
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
        if (is_opening(c))
        {
            stack[top] = c;
            top++;
        }
        else if (is_closing(c))
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