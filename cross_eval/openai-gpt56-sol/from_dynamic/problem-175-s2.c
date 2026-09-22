#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool is_valid_parentheses(const char *str)
{
    size_t balance = 0;

    if (str == NULL) {
        return false;
    }

    for (; *str != '\0'; ++str) {
        if (*str == '(') {
            ++balance;
        } else if (*str == ')') {
            if (balance == 0) {
                return false;
            }
            --balance;
        }
    }

    return balance == 0;
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    size_t length = 0;

    while (input[length] != '\0' &&
           input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (input[length] == '\r') {
        input[length] = '\0';

        if (input[length + 1] == '\n') {
            input[length + 1] = '\0';
        } else if (input[length + 1] != '\0') {
            return 1;
        }
    } else if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            return 1;
        }
    }

    if (printf("%s\n", is_valid_parentheses(input) ? "True" : "False") < 0) {
        return 1;
    }

    return 0;
}