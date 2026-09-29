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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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