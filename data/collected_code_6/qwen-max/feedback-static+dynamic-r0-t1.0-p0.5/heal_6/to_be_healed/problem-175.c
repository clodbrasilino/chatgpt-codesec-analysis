#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 2 failed: expected True, got <no output>
  */

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
    const char *test1 = "()";
    const char *test2 = "(()())";
    const char *test3 = ")(";
    const char *test4 = "(()";

    printf("%s: %s\n", test1, is_valid_parentheses(test1) ? "True" : "False");
    printf("%s: %s\n", test2, is_valid_parentheses(test2) ? "True" : "False");
    printf("%s: %s\n", test3, is_valid_parentheses(test3) ? "True" : "False");
    printf("%s: %s\n", test4, is_valid_parentheses(test4) ? "True" : "False");

    return 0;
}