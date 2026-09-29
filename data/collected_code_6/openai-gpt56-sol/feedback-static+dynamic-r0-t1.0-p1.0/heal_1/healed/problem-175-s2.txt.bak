#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool is_valid_parentheses(const char *str)
{
    size_t balance = 0;

    if (str == NULL) {
        return false;
    }

    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (str[i] == '(') {
            ++balance;
        } else if (str[i] == ')') {
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
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return 1;
    }

    if (printf("%s\n", is_valid_parentheses(input) ? "True" : "False") < 0) {
        return 1;
    }

    return 0;
}