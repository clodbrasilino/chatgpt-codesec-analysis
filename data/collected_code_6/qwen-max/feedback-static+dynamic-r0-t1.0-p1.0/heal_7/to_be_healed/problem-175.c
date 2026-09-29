#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isValidParentheses(const char* s, size_t len) {
    if (len % 2 != 0) return false;

    int stack[len];
    int top = -1;

    for (size_t i = 0; i < len; i++) {
        if (s[i] == '(') {
            stack[++top] = i;
        } else if (s[i] == ')') {
            if (top == -1) return false;
            --top;
        }
    }

    return top == -1;
}

int main() {
    const char* test1 = "()";
    const char* test2 = "(()())";
    const char* test3 = "(()";
    const char* test4 = "())(";

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%s: %s\n", test1, isValidParentheses(test1, strlen(test1)) ? "Valid" : "Invalid");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%s: %s\n", test2, isValidParentheses(test2, strlen(test2)) ? "Valid" : "Invalid");
    /* Possible weaknesses found:
     *  Condition 'isValidParentheses(test3,strlen(test3))' is always false
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Condition 'isValidParentheses(test3,strlen(test3))' is always false [knownConditionTrueFalse]
     *  Calling function 'isValidParentheses' returns 0
     */
    printf("%s: %s\n", test3, isValidParentheses(test3, strlen(test3)) ? "Valid" : "Invalid");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%s: %s\n", test4, isValidParentheses(test4, strlen(test4)) ? "Valid" : "Invalid");

    return 0;
}