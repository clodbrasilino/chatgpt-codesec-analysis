#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int max_uppercase_run(const char *str)
{
    int max_run = 0;
    int current_run = 0;
    size_t i;

    if (str == NULL)
    {
        return -1;
    }

    for (i = 0; str[i] != '\0'; i++)
    {
        if (isupper((unsigned char)str[i]))
        {
            current_run++;
            if (current_run > max_run)
            {
                max_run = current_run;
            }
        }
        else
        {
            current_run = 0;
        }
    }

    return max_run;
}

int main(void)
{
    const char *test_strings[] = {
        "Hello WORLD This IS A Test",
        "ALLCAPS",
        "nocaps",
        "MixedCASEString",
        "ABCdefGHIjklMNO",
        ""
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < num_tests; i++)
    {
        int result = max_uppercase_run(test_strings[i]);
        if (result >= 0)
        {
            printf("String %zu: \"%s\"\n", i + 1, test_strings[i]);
            printf("Max uppercase run: %d\n\n", result);
        }
        else
        {
            printf("String %zu: Invalid input\n\n", i + 1);
        }
    }

    return 0;
}