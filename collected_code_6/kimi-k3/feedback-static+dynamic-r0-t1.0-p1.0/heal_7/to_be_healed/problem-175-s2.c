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

    size_t i = 0;
    while (test_cases[i] != NULL)
    {
        printf("Input: \"%s\" -> %s\n", test_cases[i],
               is_valid_parentheses(test_cases[i]) ? "Valid" : "Invalid");
        i++;
    }

    /* Possible weaknesses found:
     *  Condition 'is_valid_parentheses(NULL)' is always false [knownConditionTrueFalse]
     *  Calling function 'is_valid_parentheses' returns 0
     *  Condition 'is_valid_parentheses(NULL)' is always false
     */
    printf("Input: NULL -> %s\n", is_valid_parentheses(NULL) ? "Valid" : "Invalid");

    return 0;
}