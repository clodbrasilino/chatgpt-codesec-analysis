#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_valid_parentheses(const char *s, size_t max_len) {
    int balance = 0;
    for (size_t i = 0; i < max_len && s[i] != '\0'; ++i) {
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
    const char *test1 = "()";
    const char *test2 = "(()())";
    const char *test3 = ")(";
    const char *test4 = "(()";

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%s: %s\n", test1, is_valid_parentheses(test1, strlen(test1)) ? "Valid" : "Invalid");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%s: %s\n", test2, is_valid_parentheses(test2, strlen(test2)) ? "Valid" : "Invalid");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%s: %s\n", test3, is_valid_parentheses(test3, strlen(test3)) ? "Valid" : "Invalid");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%s: %s\n", test4, is_valid_parentheses(test4, strlen(test4)) ? "Valid" : "Invalid");

    return 0;
}