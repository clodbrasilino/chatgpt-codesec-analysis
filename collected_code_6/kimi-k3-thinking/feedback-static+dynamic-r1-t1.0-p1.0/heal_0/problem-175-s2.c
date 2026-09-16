#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool is_valid_parentheses(const char *str)
{
    size_t balance;
    size_t i;

    if (str == NULL) {
        return false;
    }

    balance = 0;
    i = 0;
    while (str[i] != '\0') {
        if (str[i] == '(') {
            balance++;
        } else if (str[i] == ')') {
            if (balance == 0) {
                return false;
            }
            balance--;
        }
        i++;
    }

    return balance == 0;
}

int main(void)
{
    const char *tests[] = {
        "()",
        "(())",
        "(()())",
        "(()",
        "())",
        ")(",
        "",
        "(a+b)*(c-d)",
        "no parentheses"
    };
    const size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        printf("%-15s : %s\n", tests[i],
               is_valid_parentheses(tests[i]) ? "valid" : "invalid");
    }

    return 0;
}