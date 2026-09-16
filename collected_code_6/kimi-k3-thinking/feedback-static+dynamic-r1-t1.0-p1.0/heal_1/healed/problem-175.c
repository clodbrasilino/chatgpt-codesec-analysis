#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_valid_parentheses(const char *str)
{
    size_t balance = 0;
    bool valid = true;

    if (str == NULL)
    {
        valid = false;
    }
    else
    {
        for (const char *p = str; *p != '\0'; ++p)
        {
            if (*p == '(')
            {
                ++balance;
            }
            else if (*p == ')')
            {
                if (balance == 0)
                {
                    valid = false;
                    break;
                }
                --balance;
            }
            else
            {
                valid = false;
                break;
            }
        }

        if (balance != 0)
        {
            valid = false;
        }
    }

    printf("%s\n", valid ? "True" : "False");

    return valid;
}

int main(int argc, char *argv[])
{
    char buffer[65536];

    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            is_valid_parentheses(argv[i]);
        }
    }
    else
    {
        while (fgets(buffer, sizeof buffer, stdin) != NULL)
        {
            buffer[strcspn(buffer, "\r\n")] = '\0';
            is_valid_parentheses(buffer);
        }
    }

    return EXIT_SUCCESS;
}