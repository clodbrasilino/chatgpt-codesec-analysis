#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_valid_parentheses(const char *s) {
    int len = strlen(s);
    int balance = 0;
    for (int i = 0; i < len; ++i) {
        if (s[i] == '(') {
            balance++;
        } else if (s[i] == ')') {
            balance--;
            if (balance < 0) {
                return false;
            }
        }
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