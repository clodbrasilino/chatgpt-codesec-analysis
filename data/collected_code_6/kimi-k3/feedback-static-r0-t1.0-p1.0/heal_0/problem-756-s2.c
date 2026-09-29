#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_pattern(const char *str)
{
    if (str == NULL)
    {
        return false;
    }

    if (str[0] != 'a')
    {
        return false;
    }

    if (str[1] == 'b')
    {
        return str[2] == '\0';
    }

    return str[1] == '\0';
}

int main(void)
{
    const char *test_cases[] = {"a", "ab", "abb", "b", "ba", "abc", "aa"};
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++)
    {
        if (match_pattern(test_cases[i]))
        {
            printf("Match: %s\n", test_cases[i]);
        }
        else
        {
            printf("No match: %s\n", test_cases[i]);
        }
    }

    return 0;
}