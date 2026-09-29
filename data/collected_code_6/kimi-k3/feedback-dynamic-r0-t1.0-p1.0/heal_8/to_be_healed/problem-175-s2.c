#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  */

bool is_valid_parentheses(const char *s)
{
    if (s == NULL)
    {
        return false;
    }

    int balance = 0;
    size_t i = 0;

    while (s[i] != '\0')
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

    bool expected[] = {
        true,
        true,
        true,
        false,
        false,
        true,
        true,
        true,
        false,
        false
    };

    size_t i = 0;
    while (test_cases[i] != NULL)
    {
        bool result = is_valid_parentheses(test_cases[i]);
        printf("Input: \"%s\" -> %s (Expected: %s) - %s\n", 
               test_cases[i],
               result ? "Valid" : "Invalid",
               expected[i] ? "Valid" : "Invalid",
               result == expected[i] ? "PASS" : "FAIL");
        i++;
    }

    bool null_result = is_valid_parentheses(NULL);
    printf("Input: NULL -> %s (Expected: Invalid) - %s\n", 
           null_result ? "Valid" : "Invalid",
           null_result == false ? "PASS" : "FAIL");

    return 0;
}