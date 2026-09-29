#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

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

int main(int argc, char *argv[])
{
    char buffer[4096];

    if (argc > 1) {
        printf("%s\n", is_valid_parentheses(argv[1]) ? "True" : "False");
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        printf("%s\n", is_valid_parentheses(buffer) ? "True" : "False");
    }

    return 0;
}