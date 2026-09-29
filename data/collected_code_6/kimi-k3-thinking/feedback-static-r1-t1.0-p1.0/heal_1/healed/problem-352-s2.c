#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool all_characters_unique(const char *str)
{
    bool seen[256] = {false};
    size_t i;

    if (str == NULL)
    {
        return false;
    }

    for (i = 0; i <= 256; i++)
    {
        unsigned char c = (unsigned char)str[i];

        if (c == '\0')
        {
            return true;
        }

        if (seen[c])
        {
            return false;
        }

        seen[c] = true;
    }

    return false;
}

int main(void)
{
    const char *tests[] = {
        "abcdefg",
        "hello",
        "",
        "aA",
        "programming"
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < num_tests; i++)
    {
        printf("\"%s\" -> %s\n", tests[i],
               all_characters_unique(tests[i]) ? "all unique" : "duplicates found");
    }

    if (all_characters_unique(NULL))
    {
        printf("NULL -> all unique\n");
    }
    else
    {
        printf("NULL -> invalid input\n");
    }

    return 0;
}