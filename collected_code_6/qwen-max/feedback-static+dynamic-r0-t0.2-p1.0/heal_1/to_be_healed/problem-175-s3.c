#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_valid_parentheses(const char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
    const char *test_strings[] = {"()", "(()", ")()(", "(()())", "(())", "(()))("};
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (int i = 0; i < num_tests; ++i) {
        bool result = is_valid_parentheses(test_strings[i]);
        printf("%s: %s\n", test_strings[i], result ? "Valid" : "Invalid");
    }

    return 0;
}