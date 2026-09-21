#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_valid_parentheses(const char *s, size_t max_len)
{
    if (s == NULL)
    {
        return false;
    }

    size_t len = strnlen(s, max_len);
    if (len == 0)
    {
        return true;
    }

    int balance = 0;
    size_t i = 0;

    while (i < len)
    {
        if (s[i] == '(')
        {
            balance++;
        }
        else if (s[i] == ')')
        {
            balance--;
            if (balance < 0)
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        i++;
    }

    return balance == 0;
}

int main(void)
{
    const char *test_cases[] = {
        "()",
        "(())",
        "()()",
        "(()",
        "())",
        "((()))",
        "(()())",
        "",
        "abc",
        NULL
    };

    size_t i = 0;
    while (test_cases[i] != NULL)
    {
        printf("Input: \"%s\" -> %s\n", test_cases[i],
               is_valid_parentheses(test_cases[i], 256) ? "Valid" : "Invalid");
        i++;
    }

    return 0;
}