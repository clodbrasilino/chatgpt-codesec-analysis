#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  */

bool is_valid_parentheses(const char *str)
{
    bool valid = true;

    if (str != NULL)
    {
        size_t balance = 0;

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

int main(int argc, const char *argv[])
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            is_valid_parentheses(argv[i]);
        }
    }
    else
    {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[65536];

        while (fgets(buffer, sizeof buffer, stdin) != NULL)
        {
            buffer[strcspn(buffer, "\r\n")] = '\0';
            is_valid_parentheses(buffer);
        }
    }

    return EXIT_SUCCESS;
}