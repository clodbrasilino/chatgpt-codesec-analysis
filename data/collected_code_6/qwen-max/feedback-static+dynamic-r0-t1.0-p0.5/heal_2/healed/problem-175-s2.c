#include <stdio.h>
#include <stdbool.h>

bool is_valid_parentheses(const char *s) {
    int balance = 0;
    while (*s) {
        if (*s == '(') {
            balance++;
        } else if (*s == ')') {
            if (balance == 0) {
                return false;
            }
            balance--;
        }
        s++;
    }
    return balance == 0;
}

int main() {
    const char *test_strings[] = {"()", "(()())", ")(", "(()", "())("};
    for (int i = 0; i < 5; ++i) {
        printf("%s: %s\n", test_strings[i], is_valid_parentheses(test_strings[i]) ? "Valid" : "Invalid");
    }
    return 0;
}