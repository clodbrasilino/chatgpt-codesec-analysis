#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_valid_parentheses(const char *str) {
    int len = strlen(str);
    int balance = 0;
    for (int i = 0; i < len; ++i) {
        if (str[i] == '(') {
            balance++;
        } else if (str[i] == ')') {
            balance--;
            if (balance < 0) {
                return false;
            }
        }
    }
    return balance == 0;
}

int main() {
    const char *test1 = "()";
    const char *test2 = "(()())";
    const char *test3 = ")(";
    const char *test4 = "(()";

    printf("%s: %s\n", test1, is_valid_parentheses(test1) ? "Valid" : "Invalid");
    printf("%s: %s\n", test2, is_valid_parentheses(test2) ? "Valid" : "Invalid");
    printf("%s: %s\n", test3, is_valid_parentheses(test3) ? "Valid" : "Invalid");
    printf("%s: %s\n", test4, is_valid_parentheses(test4) ? "Valid" : "Invalid");

    return 0;
}